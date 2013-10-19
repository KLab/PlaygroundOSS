/* 
   Copyright 2013 KLab Inc.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
package klb.android.GameEngine;

import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.WindowManager;
import android.annotation.TargetApi;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.ActivityNotFoundException;
import android.content.BroadcastReceiver;
import android.content.DialogInterface;
import android.content.Context;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.content.res.AssetManager;
import android.hardware.SensorManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.view.OrientationEventListener;
import android.content.res.Configuration;
import android.widget.FrameLayout;
import android.widget.Toast;
import android.view.ViewGroup;
import com.google.android.gcm.GCMRegistrar;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.Intent;
import android.net.Uri;
import android.media.AudioManager;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.lang.ref.WeakReference;

import klb.android.GameEngine.billing.manager.BillingManager;

public class GameEngineActivity extends Activity {
	private static final boolean USE_SD_CARD = false;  // SDカード優先フラグ
	OrientationEventListener mOrientationListener;
	private static AssetManager mAssetMgr = null;
	private GameGLSurfaceView mView;
	private String c_path_install; 
	private String c_path_external;
    private String c_path_base;
	private boolean m_initialized = false;
	private int	m_prev_orientation;
	private FrameLayout m_layout = null;
	public FrameLayout m_MovieLayout = null;
	public FrameLayout m_IndicatorLayout = null;
	private ApplicationInfo m_appliInfo = null;
	final private String VERSION_KEY = "[assets]version";
	private View m_InstallProgressView = null;
	private boolean m_installEnd = false;
	private boolean m_UsePause = false;
	private boolean headsetEquipped = false;
	private int m_mediaVolume = 0;
	private BroadcastReceiver headsetReceiver = null;
	private Thread installThread = null;
	private long activityCreatedAt = 0;
    final int DEFAULT_VOLUME = 5;

	// AlertDialog用
	private String m_alertTitle = null;
	private String m_alertMessage = null;

	private boolean isSuBinaryPresent() {
		String[] locationCandidates = { "/data/local", "/data/local/bin",
				"/data/local/xbin", "/sbin", "/system/bin", "/system/sd/xbin",
				"/system/xbin", "/system/bin/failsafe", "/vendor/bin" };
		for (String candidateDir : locationCandidates) {
			String candidate = candidateDir + "/su";
			try {
				File f = new File(candidate);
				if (f.exists()) {
					return true;
				}
			} catch (Exception e) {

			}
		}
		try {
			File f = new File("/system/app/Superuser.apk");
			if (f.exists()) {
				return true;
			}
		} catch (Exception e) {

		}
		return false;
	}
	
	private boolean isInappropriateEnvSuspected() {
		if ((getApplicationInfo().flags & ApplicationInfo.FLAG_DEBUGGABLE) == 0) {
			return Build.PRODUCT.equals("google_sdk") || Build.PRODUCT.equals("sdk") || isSuBinaryPresent();
		}
		return false;
	}

	public void startActivity(final Intent intent) {
		final Context ctx = this.getApplicationContext();
		intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		new Thread(new Runnable() {
			@Override
			public void run() {
				try {
					if (installThread != null) {
						installThread.join();
					}
					long sleepRemaining = 1000 - ((PFInterface.nanotime() - activityCreatedAt) / 1000000);
					if (0 < sleepRemaining) {
						Thread.sleep(sleepRemaining);
					}
				} catch (InterruptedException e) {
					return;
				}
				ctx.startActivity(intent);
			}
		}).start();
	}

	@SuppressWarnings("unused")
	@Override
    protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        activityCreatedAt = PFInterface.nanotime();
        if (isInappropriateEnvSuspected()) {
			Toast.makeText(this, "不正なアクセスを検出しました。アプリを起動出来ません。", Toast.LENGTH_LONG).show();
			finish();
			return;
		}
		// ボリュームボタンでの制御をメディア音量のみにする
		setVolumeControlStream(AudioManager.STREAM_MUSIC);
    	instanciateEarphoneChecker(); // イヤホンの接続状態の監視を設定
		
        // SenderIDをマニフェストから取得する
        String SenderID = null;
        try {
        	m_appliInfo = getPackageManager().getApplicationInfo(getPackageName(), PackageManager.GET_META_DATA);
            SenderID = m_appliInfo.metaData.getString("GCM_SENDER_ID");
            if(SenderID.equals("")) SenderID = null;
        } catch(PackageManager.NameNotFoundException e) {
        	Log.v("GE", "GCM SenderID Not Found.");
        	SenderID = null;
        }
        
        if(!m_initialized) {
        	boolean install_sd = false;
            String state = Environment.getExternalStorageState();
     
            // AssetsManager設定
            mAssetMgr = getResources().getAssets();

			if( USE_SD_CARD==true )
			{
				if( Environment.MEDIA_MOUNTED.equals(state) )
				{// SDがマウントされている
					// 容量チェック
        		
					// 容量が十分空いている
					install_sd = true;

					if( Environment.MEDIA_MOUNTED_READ_ONLY.equals(state) )
					{// マウントされているが、READ_ONLY
						install_sd = false;
					}
				}
				else
				{
					install_sd = false;
				}
			}

        	if( install_sd==true )
			{
        		c_path_base = this.getExternalFilesDir(null).getAbsolutePath();
				if( c_path_base==null )
				{// これでいけるか…？
					c_path_base = this.getFilesDir().getAbsolutePath();
				}
        	}
			else
			{
        		c_path_base = this.getFilesDir().getAbsolutePath();
			}
			Log.d("GameEngineActivity","FileDir:"+c_path_base);
        	
        	m_prev_orientation = 0;
        	c_path_install =  c_path_base + "/install/";
        	c_path_external = c_path_base + "/external/";

        	// install / external に相当するディレクトリ文字列を PFInterface に渡しておく　
        	PFInterface.getInstance().setBasePath(c_path_install, c_path_external);
        	PFInterface.getInstance().setSenderID(SenderID);
        	PFInterface.getInstance().setContext(this);
        	
        	// instalフォルダが無ければ生成
        	File installdir = new File(c_path_install);
    		if(!installdir.exists()) installdir.mkdir();	// ディレクトリが無ければ生成
    		
    		// externalフォルダが無ければ生成
        	File externaldir = new File(c_path_external);
    		if(!externaldir.exists()) externaldir.mkdir();	// ディレクトリが無ければ生成

    		// unzipは別スレッドで行うことにしました  2013/04/22  
    		// assets/sound の内容をfile://install/ にコピーする。
            //	unzipAssets(c_path_install, c_path_external, "AppAssets.zip");
	    	// copyAssets(c_path_install);	// assets の内容を、ローカルにコピーする
        	
        	// GCMの RegistrationId を取得
        	queryRegID(SenderID);
        	
        	m_MovieLayout = new FrameLayout(this);	// BackgroundMovieはここに組み込む
        	m_IndicatorLayout = new FrameLayout(this);
//        	mView = new GameGLSurfaceView(this, getPackageName());
        	mView = new GameGLSurfaceView(this, c_path_base );
        	m_layout = new FrameLayout(this);
        	m_layout.addView(m_MovieLayout, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
        	m_layout.addView(mView, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
        	m_layout.addView(m_IndicatorLayout, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
        	setContentView(m_layout);
        	
        	mOrientationListener = new OrientationEventListener(this, SensorManager.SENSOR_DELAY_UI) {
        		@Override
        		public void onOrientationChanged(int orientation) {
        			int ori = ((orientation + 405) % 360) / 90;
        			if(ori != m_prev_orientation) {
        				// すくなくとも90度以上回転したことを検知        				
        				Configuration config = getResources().getConfiguration();
        				switch(config.orientation)
        				{
        				case Configuration.ORIENTATION_LANDSCAPE:
        					ori = 1;
        					break;
        				case Configuration.ORIENTATION_PORTRAIT:
        					ori = 0;
        					break;
        				default:
        					break;	
        				}        				
        				m_prev_orientation = ori;
        				PFInterface.getInstance().screenRotation(ori);
        			}
        		}
        	};
        	mOrientationListener.enable();
        	m_initialized = true;
        	
        	// インストール用インジケータ（円のプログレスバー使用)  2013/04/22  
        	m_InstallProgressView = this.getLayoutInflater().inflate(R.layout.install, null);
        	m_layout.addView(m_InstallProgressView);
        	installThread = new Thread(new CInstall());
        	installThread.start();
        }
    }

    @Override
    protected void onRestart() {
        super.onRestart();
        mView.onRestart();
    }

    @Override
    protected void onPause() {
        super.onPause();

        unregisterHeadsetReceiver();
        
        mView.onPause();
        m_UsePause = true;
    }

	boolean isWindowFocused = true;
    boolean resumeRequested = false;
    @Override
	public void onWindowFocusChanged(boolean hasFocus) {
		invalidateSystemUi();
    	isWindowFocused = hasFocus;
    	if (resumeRequested) {
			resumeView();
    		resumeRequested = false;
    	}
    }

	boolean isSystemUiDirty = false;
	private void invalidateSystemUi() {
		isSystemUiDirty = true;
	}

	@TargetApi(Build.VERSION_CODES.ICE_CREAM_SANDWICH)
	public void refreshSystemUi() {
		if (isSystemUiDirty) {
			if (Build.VERSION_CODES.ICE_CREAM_SANDWICH <= Build.VERSION.SDK_INT) {
				getWindow().getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_LOW_PROFILE);
			}
			isSystemUiDirty = false;
		}
	}

    @Override
    protected void onResume() {
        super.onResume();
        m_UsePause = false;
    	invalidateSystemUi();
        
    	setMannerMode();
    	// イヤホンのレシーバーを登録
        registerHeadsetReceiver();
        
        if (!isWindowFocused) {
        	resumeRequested = true;
        }
        else {
        	resumeView();
        }
    }

	private void resumeView() {
		if (isInappropriateEnvSuspected()) {
			Toast.makeText(this, "不正なアクセスを検出しました。アプリを起動出来ません。", Toast.LENGTH_LONG).show();
			finish();
		}
		else {
			refreshSystemUi();
			mView.onResume();
		}
	}

    @Override
    protected void onDestroy() {
    	super.onDestroy();
    	PFInterface.billingTerminate();
    }
    
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
    	if (!BillingManager.getInstance(this).onActivityResult(requestCode, resultCode, data)) {
    		super.onActivityResult(requestCode, resultCode, data);
    	} else {
    		Log.d("GameEngineActivity", "handled IAB ActivityResult:" + requestCode + ":" + resultCode);
    	}
    }
 
    @Override
    public void onConfigurationChanged(Configuration newConfig) {
    	super.onConfigurationChanged(newConfig);
    }

    /**
     * handle device keys
     */
    @Override
    public boolean dispatchKeyEvent(KeyEvent event)
    {
        if( event.getAction()==KeyEvent.ACTION_DOWN )
        {
            switch( event.getKeyCode() )
            {
            case KeyEvent.KEYCODE_BACK:
            	PFInterface.getInstance().inputDeviceKey(PFInterface.DeviceKeyMap.BACK, PFInterface.DeviceKeyEvent.CLICK);
            	// suppress finishing Activity
                return true;

            case KeyEvent.KEYCODE_MENU:
            	PFInterface.getInstance().inputDeviceKey(PFInterface.DeviceKeyMap.MENU, PFInterface.DeviceKeyEvent.CLICK);
            	// suppress finishing Activity
                return true;
            }
        }
        return super.dispatchKeyEvent(event);
    }
 
    // assets 以下の指定されたzipファイルをローカルにコピーする。
    private boolean unzipAssets(String targetPath, String externalPath, String zipfile) {
    	try {
    		AssetManager assetManager = getResources().getAssets();
    		// 現在 assets に置かれている .zip が、展開済みのバージョンと同じものであるかを確認する。
    		
    		// assets フォルダにあるversionファイルを読み込む
    		InputStream verStream = assetManager.open("version");
    		Reader r = new InputStreamReader(verStream);
    		BufferedReader br = new BufferedReader(r);
    		String verLine = br.readLine();
    		br.close();
    		r.close();
    		verStream.close();
    		
    		// SharedPreferences に登録されているキー "[assets]version" の値が、現在展開済みのバージョン
    		SharedPreferences pref = getPreferences(Context.MODE_PRIVATE);
    		String ret = pref.getString(VERSION_KEY, "");
    		
    		// 展開済みバージョンと、versionファイルの内容を比較して、同じであれば展開済みとする。
    		if(ret.equals(verLine)) return true;
    		
    		// 展開済みのものと異なる場合は再展開する。
    		// 一旦ディレクトリ内容を削除する。
    		Runtime localRuntime = Runtime.getRuntime();
    		String cmd = "rm -R " + targetPath + "/*";
    		try {
    			localRuntime.exec(cmd);
    		} catch(IOException ex) {
    			return false;
    		}
    		
    		// externalフォルダが無ければ生成
        	File externaldir = new File(externalPath);
    		if(!externaldir.exists()) externaldir.mkdir();	// ディレクトリが無ければ生成
    		
    		// ディレクトリ作成
    		File dir = new File(targetPath);
    		if(!dir.exists()) dir.mkdir();	// ディレクトリが無ければ生成

    		InputStream inputStream = assetManager.open(zipfile);
    		ZipInputStream zipInputStream = new ZipInputStream(inputStream);
    		ZipEntry zipEntry = zipInputStream.getNextEntry();
    		while(zipEntry != null) {
    			String entryName = zipEntry.getName();
    			int n;
    			String outpath = targetPath + entryName;
    		//	Log.d("Cpp", "OutPath:" + outpath);
    			// ディレクトリであれば、そのディレクトリを作成して次へ
    			if(zipEntry.isDirectory()) {
    				File underDir = new File(outpath);
    				if(!underDir.exists()) underDir.mkdirs();
    				zipInputStream.closeEntry();
    				zipEntry = zipInputStream.getNextEntry();
    				continue;
    			}
    			// 親ディレクトリが無い場合は作成
    			File file = new File(outpath);
    			File underDir = file.getParentFile();
    			if(!underDir.exists()) {
    				underDir.mkdirs();
    			}
    			// FileOutputStream fileOutputStream = openFileOutput(outpath, MODE_WORLD_READABLE);
    			FileOutputStream fileOutputStream = new FileOutputStream(outpath);
				int DEFAULT_BUFSIZ = 1024 * 4;
				byte [] buf = new byte [ DEFAULT_BUFSIZ ];
				while((n = zipInputStream.read(buf, 0, DEFAULT_BUFSIZ)) > -1) {
					fileOutputStream.write(buf, 0, n);
				}
				fileOutputStream.close();
				zipInputStream.closeEntry();
				zipEntry = zipInputStream.getNextEntry();
    		}
    		zipInputStream.close();
    		
    		// 展開が完了したので、現在のversionの内容をSharedPreferencesに記録する。
    		SharedPreferences.Editor e = pref.edit();
    		e.putString(VERSION_KEY, verLine);
    		e.commit();

    		return true;
    	} catch(IOException ex) {
    		return false;
    	}
    }

    public boolean putControl(View view, int x, int y, int width, int height) {
    	if(width == 0 || height == 0) return false;
    	ViewGroup.LayoutParams param = new ViewGroup.LayoutParams(width, height);
    	m_layout.addView(view, param);
    	return true;
    }
    
    public boolean replaceView(View view, int x, int y, int width, int height) {
    	m_layout.removeView(view);
    	return putControl(view, x, y, width, height);
    	// return true;
    }
    
    public void removeView(View view) {
    	m_layout.removeView(view);
    }
    
    public void queryRegID(String SenderID) {
    	if(SenderID == null) return;
  
    	// GCMの RegistrationId を取得
        GCMRegistrar.checkDevice(getApplicationContext());
        GCMRegistrar.checkManifest(getApplicationContext());
        String regId = GCMRegistrar.getRegistrationId(getApplicationContext());
        if(regId.equals("")) {
        	GCMRegistrar.register(getApplicationContext(), SenderID);
        } else {
        	PFInterface.getInstance().setRegistrationID(regId);
        	Log.v("Cpp", "Already registered.");
        }
    }
    
    /*!
     * @brief	AssetsManager取得
     */
    public static AssetManager GetAssetManager()
    {
    	return mAssetMgr;
    }
    
    // 別スレッドでのインストール
    private class CInstall implements Runnable {
    	@Override
		public void run()
    	{
    		unzipAssets(c_path_install, c_path_external, "AppAssets.zip");
    		handler.sendEmptyMessage(0);
    	}
    }
    
    // インストール終了時処理
    private static class InstallationPostProcessHandler extends Handler {
        private final WeakReference<GameEngineActivity> mActivity;
        public InstallationPostProcessHandler(GameEngineActivity activity) {
            mActivity = new WeakReference<GameEngineActivity>(activity);
        }

        @Override
        public void handleMessage(Message msg) {
            final GameEngineActivity self = mActivity.get();
            if (self == null) {
                return;
            }
            self.m_layout.removeView(self.m_InstallProgressView);
            self.m_InstallProgressView = null;
            self.m_installEnd = true;
            Log.v("Cpp", "InstallEnd");
        }
    }

    private Handler handler = new InstallationPostProcessHandler(this);
    
    public boolean IsInstallEnd() {
    	return m_installEnd;
    }

    boolean isMannerModeOn = false;
    boolean isWearingHeadset = false;

    /**
     * update volume using device's manner mode settings and head-set plug status
     */
    public void setMannerMode()
    {
    	AudioManager audioManager = (AudioManager)getSystemService(Context.AUDIO_SERVICE);
		int mediaVolume = audioManager.getStreamVolume(AudioManager.STREAM_MUSIC);
		int mode = audioManager.getRingerMode();
		boolean bManner = (mode == AudioManager.RINGER_MODE_SILENT || mode == AudioManager.RINGER_MODE_VIBRATE);

		if (isMannerModeOn == bManner && isWearingHeadset == headsetEquipped) {
			return;
		}
		
		if (!isMannerModeOn && bManner) {
			// manner mode turned on
			if (!isWearingHeadset && headsetEquipped) {
				// head-set on
				m_mediaVolume = DEFAULT_VOLUME;
			}
			else if (isWearingHeadset && headsetEquipped) {
				// head-set kept on
				m_mediaVolume = mediaVolume;
			}
			else if ((!isWearingHeadset && !headsetEquipped) || (isWearingHeadset && !headsetEquipped)) {
				// head-set kept off or turned off
				m_mediaVolume = 0;
			}
		}
		else if (isMannerModeOn && !bManner) {
			// manner mode turned off
			if (!isWearingHeadset && headsetEquipped) {
				// head-set turned on
				m_mediaVolume = DEFAULT_VOLUME;
			}
			else if (isWearingHeadset == headsetEquipped) {
				// head-set kept (on or off)
				m_mediaVolume = mediaVolume;
			}
			else {
				// head-set turned off
				// this setting could be dependent on game policy
				m_mediaVolume = 0;
			}
		}
		else {
			if (isMannerModeOn) {
				// manner mode kept on
				if (!isWearingHeadset && headsetEquipped) {
					// head-set turned on
					m_mediaVolume = DEFAULT_VOLUME;
				}
				else if (isWearingHeadset == headsetEquipped) {
					// head-set kept (on or off)
					m_mediaVolume = mediaVolume;
				}
				else {
					// head-set turned off
					m_mediaVolume = 0;
				}
			}
			else if (!isMannerModeOn) {
				// manner mode kept still off
				if (!isWearingHeadset && headsetEquipped) {
					// head-set turned on
					m_mediaVolume = DEFAULT_VOLUME;
				}
				else if (isWearingHeadset == headsetEquipped) {
					// head-set kept (on or off)
					m_mediaVolume = mediaVolume;
				}
				else {
					// head-set turned off
					m_mediaVolume = 0;
				}
			}
		}
		if (m_mediaVolume != mediaVolume) {
			audioManager.setStreamVolume(AudioManager.STREAM_MUSIC, m_mediaVolume, 0);
		}
		isMannerModeOn = bManner;
		isWearingHeadset = headsetEquipped;
    }
    
    //! イヤホン状態をチェック
  	public void instanciateEarphoneChecker() {
  		headsetReceiver = new BroadcastReceiver() {
  			@Override
  		    public void onReceive(Context context, Intent intent) {
  		        if (intent.getAction().equalsIgnoreCase(Intent.ACTION_HEADSET_PLUG)) {
  		            headsetEquipped = (intent.getIntExtra("state", 0) == 1);
  		            
  		            // マナーモードチェック
  		            setMannerMode();
  		        }
  		    }
  		};
  	}
  	
  	//! イヤホンのレシーバーを登録
  	private void registerHeadsetReceiver()
  	{
  		if( headsetReceiver != null ) {
  			this.registerReceiver(headsetReceiver, new IntentFilter(Intent.ACTION_HEADSET_PLUG));
  		}
  	}
  	
  	//! イヤホンのレシーバーを解除
  	private void unregisterHeadsetReceiver()
  	{
  		if( headsetReceiver != null ) {
  			unregisterReceiver(headsetReceiver);
  		}
  	}

	// メーラー起動
    public void startExternalApplicationMail(String addr , String subject , String body)
    {
    	Intent intent = new Intent(Intent.ACTION_SENDTO);
    	intent.setData(Uri.parse("mailto:"+addr));
    	intent.putExtra(Intent.EXTRA_SUBJECT, subject);
    	intent.putExtra(Intent.EXTRA_TEXT, body);
		try {
			super.startActivity(intent);
		} catch (ActivityNotFoundException e) {
			startAlertDialog( "Alert" , "メーラーを有効にして下さい" );
		}
    }
    // アラートダイアログ起動
    public void startAlertDialog( String title , String message )
    {
    	m_alertTitle = title;
    	m_alertMessage = message;
		runOnUiThread(new Runnable() {
            @Override
			public void run() {
					//^^^^^
            		//Context context = getApplicationContext();
                    AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(GameEngineActivity.this);
                    // アラートダイアログのタイトルを設定します
                    alertDialogBuilder.setTitle( m_alertTitle );
                    // アラートダイアログのメッセージを設定します
                    alertDialogBuilder.setMessage( m_alertMessage );
                    // アラートダイアログの肯定ボタンがクリックされた時に呼び出されるコールバックリスナーを登録します
                    alertDialogBuilder.setPositiveButton("OK",
                            new DialogInterface.OnClickListener() {
                                @Override
                                public void onClick(DialogInterface dialog, int which) {
                                }
                            });       
                    // アラートダイアログのキャンセルが可能かどうかを設定します
                    alertDialogBuilder.setCancelable(false);
                    AlertDialog alertDialog = alertDialogBuilder.create();
                    // アラートダイアログを表示します
                    alertDialog.show();
            }
        });        		    	
    }
    
    // ブラウザ起動
    public void startBrowser( String url )
    {
        Uri uri = Uri.parse(url);
    	Intent i = new Intent(Intent.ACTION_VIEW,uri);
    	startActivity(i);
    }

	public boolean IsUsePause()
    {
    	return m_UsePause;
    }
    public void SetUsePause(boolean bUsePause)
    {
    	m_UsePause = bUsePause;
    }

	public void forbidSleep(final boolean isForbidden) {
		runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (isForbidden) {
					getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
				}
				else {
					getWindow().clearFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
				}
			}
		});
	}
}
