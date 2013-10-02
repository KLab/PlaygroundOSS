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
/*!
 ¥brief C++実装部分とのインタフェースを採るプラットフォームモジュール
 ¥file PFInterface.java
 */
package klb.android.GameEngine;

import android.content.Context;
import klb.android.GameEngine.EditBoxItem;
import klb.android.GameEngine.GameEngineActivity;
import klb.android.GameEngine.MovieViewItem;
import klb.android.GameEngine.WebViewItem;
import klb.android.GameEngine.billing.manager.BillingManager;

import android.graphics.Paint;
import android.graphics.Canvas;
import android.graphics.Bitmap;
import android.os.Build;
import android.util.Log;
import android.view.Gravity;
import android.webkit.WebView;
import android.content.SharedPreferences;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;

import java.lang.String;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.io.UnsupportedEncodingException;

import org.json.JSONArray;
import org.json.JSONException;

public class PFInterface {
	public static int MOVIE_FINISHED = 1;
	
	// エターナルスタティックファイナル ------- 順番を間違えると相手は死ぬ 
	public static final int E_STORE_BAD_ITEMID = 0;         // アイテムIDが無効
	public static final int E_STORE_GET_PRODUCTS = 1; // ProductListの取得.
	public static final int E_STORE_PURCHASHING = 2;        // 購入処理中
	public static final int E_STORE_PURCHASHED = 3;         // 購入処理終了
	public static final int E_STORE_FAILED = 4;             // 購入処理失敗
	public static final int E_STORE_RESTORE = 5;            // リストア終了
	public static final int E_STORE_RESTORE_FAILED = 6;     // リストア失敗
	public static final int E_STORE_RESTORE_COMPLETED = 7;  // 全リストア終了

    // エターナルスタティックファイナル ------- 順番を間違えると相手は死なないけど困る
    // CPFInterface.h の IClientRequest 内に定義された enum INPUT_TYPE と対応するようにメンテナンスすること
    public static final int E_INPUT_TYPE_CLICK   = 0; //!< マウスのクリック、タッチパネルのタップ動作
    public static final int E_INPUT_TYPE_DRAG    = 1; //!< ドラッグ動作
    public static final int E_INPUT_TYPE_RELEASE = 2; //!< リリース動作(離す)
    public static final int E_INPUT_TYPE_CANCEL  = 3; //!< Cancel event

	public enum WEBVIEW_STATUS {
		E_DIDSTARTLOADWEB(0),
		E_DIDLOADENDWEB(1),
		E_FAILEDLOADWEB(2),
		E_URLJUMP(3);
		
		private int m_num;
		private WEBVIEW_STATUS(int _num) {
			m_num = _num;
		}
		
		public int GetNum() { return m_num; }
	}
	
	public class DeviceKeyMap {
		public static final int BACK = 0x00000001;
		public static final int MENU = 0x00000002;
	}
	
	public class DeviceKeyEvent {
		public static final char PRESS = 0x01;
		public static final char RELEASE = 0x02;
		public static final char CLICK = 0x03;
	}
	
	// Java の Singleton 流儀。
	private static PFInterface instance = new PFInterface();	// インスタンス実体はこのメンバ
	private static String m_path_external = null;
	private static String m_path_install = null;
	private	int	m_width;
	private int m_height;
	private boolean m_bexec = false;
	private GameEngineActivity m_context = null;
	private String m_osversion = null;
	private String m_tzone = null;
	private int MAX_EDIT_TEXT = 100;
	private int MAX_WEB_VIEW = 100;
	private int MAX_MOVIE_VIEW = 50;

	private String m_senderId = null;
	private String m_registrationId = null;

	private EditBoxItem[] m_textList = new EditBoxItem [ MAX_EDIT_TEXT ];	// TextBox の配列
	private int m_textListCount = -1;

	private WebViewItem[] m_webList = new WebViewItem [ MAX_WEB_VIEW ];		// WebView の配列
	private int m_webListCount = -1;
	
	private MovieViewItem[] m_movieList = new MovieViewItem [ MAX_MOVIE_VIEW ];
	private int m_movieListCount = -1;

	private IndicatorItem m_indicator;

	private PFInterface() {}

	//! インスタンス取得メソッド
	/*!
	 \return 唯一のインスタンス
	 Singleton 実装されたPFInstanceのインスタンスを取得する。
	 */
	public static PFInterface getInstance() {
		return instance;
	}
	
	public void setSenderID(String senderId) {
		m_senderId = senderId;
	}
	
	public String getSenderID() {
		return m_senderId;
	}
	
	public void setRegistrationID(String regId) {
		m_registrationId = regId;
	}
	
	public String getRegistrationID() {
		return m_registrationId;
	}
	
	public String readyRegIDPublic() {
		if(m_registrationId == null) m_context.queryRegID(m_senderId);
		return m_registrationId;
	}

	public void setContext(GameEngineActivity context) {
		m_context = context;
		for(int i = 0; i < MAX_EDIT_TEXT; i++) m_textList[i] = null;
		for(int i = 0; i < MAX_WEB_VIEW; i++) m_webList[i] = null;
	}
	
	public void setBasePath(String path_install, String path_external) {
		m_path_external = path_external;
		m_path_install = path_install;
	}
	
	// 
	public static String readyRegID() {
		String regist = getInstance().readyRegIDPublic();
		return regist;
	}
	
	//! UUIDを生成するメソッド。keychain機能で使用される。
	public static String genUserID() {
		String uuid = UUID.randomUUID().toString();
		return uuid;
	}

	//! SHA512を生成
	public static byte[] sha512(String string) {
		try {
			MessageDigest md = MessageDigest.getInstance("SHA-512");
			byte[] strdata = string.getBytes("UTF-8");
			byte[] digest = md.digest(strdata);
			return digest;
		} catch(NoSuchAlgorithmException e) {
			throw new RuntimeException("No Such Algorithm: SHA512");
		} catch(UnsupportedEncodingException e) {
			throw new RuntimeException("No Such Algorithm: SHA512");
		}
	}
	
	//! keychain 機能 I/F (native から登録要求を受ける口)
	public static boolean setKeyChain(String service_name, String key, String value) {
		SharedPreferences pref = getInstance().m_context.getPreferences(Context.MODE_PRIVATE);
		String pkey = "[" + service_name + "]" + key;
		SharedPreferences.Editor e = pref.edit();
		e.putString(pkey, value);
		e.commit();
		return true;
	}
	
	//! keychain 機能 I/F (native から取得要求を受ける口)
	public static String getKeyChain(String service_name, String key) {
		SharedPreferences pref = getInstance().m_context.getPreferences(Context.MODE_PRIVATE);
		String pkey = "[" + service_name + "]" + key;
		String ret = pref.getString(pkey, "");
		return ret;
	}
		
	//! keychain 機能 I/F (native から取得要求を受ける口)
	public static boolean delKeyChain(String service_name, String key) {
		SharedPreferences pref = getInstance().m_context.getPreferences(Context.MODE_PRIVATE);
		String pkey = "[" + service_name + "]" + key;
		SharedPreferences.Editor e = pref.edit();
        e.remove(pkey);
        e.commit();
		return true;
	}

	//! TextBox を作る
	public static int textbox_create(int x, int y, int width, int height, String defText, boolean passwdmode) {
		PFInterface pfif = PFInterface.getInstance();
		GameEngineActivity context = pfif.m_context;
		EditBoxItem ebox = new EditBoxItem(context, defText, x, y, width, height, passwdmode);
		for(int i = 0; i < pfif.MAX_EDIT_TEXT; i++) {
			if(pfif.m_textList[i] == null) {
				pfif.m_textList[i] = ebox;
				if(i > pfif.m_textListCount) pfif.m_textListCount = i;
				return i;
			}
		}
		ebox = null;
		return -1;
	}
	
	//! 指定された TextBox を破棄する
	public static boolean textbox_destroy(int index) {
		PFInterface pfif = PFInterface.getInstance();
		EditBoxItem edit = pfif.m_textList[index];
		edit.m_remove = true;
		return true;
	}
	
	//! TextBoxに文字列を設定
	public static boolean textbox_setText(int index, String text) {
		final EditBoxItem control = PFInterface.getInstance().m_textList[index];
		final String inner_text = text;
		if(control == null) return false;
		// 平成25年8月14日(水)
		// EditBoxItemが動いているThread以外からsetTextがcallされる可能性があり、
		// その場合にCalledFromWrongThreadExceptionが投げられてしまうので
		// ActivityのrunOnUiThreadを利用してEditBoxItemが動いているThread上でsetTextがcallされるよう修正.
		PFInterface.getInstance().m_context.runOnUiThread(new Runnable() {
				public void run() {
						control.setText(inner_text);
				}
		});
		return true;
	}
	
	//! TextBoxから文字列を取得
	public static String textbox_getText(int index) {
		EditBoxItem control = PFInterface.getInstance().m_textList[index];
		if(control == null) return null;
		String text = control.getText();
		return text;
	}

	//! TextBox の位置やサイズ,表示状態,有効/無効を変更
	public static void textbox_update(int index, int x, int y, int width, int height, boolean enable, boolean visible) {
		PFInterface pfif = PFInterface.getInstance();
		EditBoxItem edit = pfif.m_textList[index];
		if(edit == null) return;

		edit.move(x, y, width, height);
		edit.setVisible(visible);
		edit.setEnable(enable);
	}
	
	//
	public static void textbox_setpaint(int index, Paint paint)
	{
		PFInterface pfif = PFInterface.getInstance();
		EditBoxItem edit = pfif.m_textList[index];
		if(edit == null) return;
		
		edit.setPaint(paint);
	}
	
	// 
	public static void textbox_sethint(int index, String hint)
	{
		PFInterface pfif = PFInterface.getInstance();
		EditBoxItem edit = pfif.m_textList[index];
		if(edit == null) return;
		
		edit.setHint(hint);
	}

	public static void textbox_setMaxlen(int index, int maxlen)
	{
		PFInterface pfif = PFInterface.getInstance();
		EditBoxItem edit = pfif.m_textList[index];
		if(edit == null) return;

		edit.setMaxlen(maxlen);
	}

	static final int TX_ALIGN_LEFT = 0;
	static final int TX_ALIGN_CENTER = 1;
	static final int TX_ALIGN_RIGHT = 2;
	public static void textbox_setAlignment(int index, int alignment)
	{
		PFInterface pfif = PFInterface.getInstance();
		EditBoxItem edit = pfif.m_textList[index];
		if(edit == null) return;

		int gravity = 0;
		switch (alignment) {
		case TX_ALIGN_LEFT:
			gravity = Gravity.LEFT;
			break;
		case TX_ALIGN_CENTER:
			gravity = Gravity.CENTER;
			break;
		case TX_ALIGN_RIGHT:
			gravity = Gravity.RIGHT;
			break;
		}
		edit.setGravity(gravity);
	}

	//! WebViewの生成
	public static int webview_create(int x, int y, int width, int height,
									String defURL, 
									String token, String region, String client, String consumerKey,
									String applicationId, String userId, boolean nojump) {
		
		PFInterface pfif = PFInterface.getInstance();
		GameEngineActivity context = pfif.m_context;
		WebViewItem web = new WebViewItem(context, defURL, x, y, width, height,
										token, region, client, consumerKey, applicationId, userId,
										pfif.m_tzone, pfif.m_osversion, nojump);
		for(int i = 0; i < pfif.MAX_WEB_VIEW; i++) {
			if(pfif.m_webList[i] == null) {
				pfif.m_webList[i] = web;
				if(i > pfif.m_webListCount) pfif.m_webListCount = i;
				return i;
			}
		}
		web = null;
		return -1;
	}

	//! WebViewの破棄
	public static boolean webview_destroy(int index) {
		PFInterface pfif = PFInterface.getInstance();
		WebViewItem web = pfif.m_webList[index];
		web.m_remove = true;
		return true;
	}

	//! WebViewにURLを設定
	public static boolean webview_setText(int index, String text) {
		final WebViewItem control = PFInterface.getInstance().m_webList[index];
		final String inner_text = text;
		if(control == null) return false;
		// 平成25年8月15日(木)
		// EditBoxに習い修正
		PFInterface.getInstance().m_context.runOnUiThread(new Runnable() {
				public void run() {
						control.setText(inner_text);
				}
		});
		return true;
	}
	
	//! WebViewからWebViewItemを取得
	public static int webview_getWebViewItem(WebView _webView) {
		PFInterface pfif = PFInterface.getInstance();
		for(int i = 0; i < pfif.MAX_WEB_VIEW; i++)
		{
			if(pfif.m_webList[i] != null && pfif.m_webList[i].isEqual(_webView)) {
				return i;
			}
		}
		return -1;
	}
	
	//! WebViewの拡大縮小設定
	public static void webview_setZoom(int _index, boolean _flg)
	{
		WebViewItem control = PFInterface.getInstance().m_webList[_index];
		if(control == null) return;
		control.setZoom(_flg);
	}
	
	//! WebViewの背景色を設定
	public static void webview_setColor(int _index, int _alpha, int _col) 
	{
		WebViewItem control = PFInterface.getInstance().m_webList[_index];
		if(control == null) return;
		control.setColor(_alpha, _col);
	}
	
	//! WebViewから文字列を取得
	public static String webview_getText(int index) {
		WebViewItem control = PFInterface.getInstance().m_webList[index];
		if(control == null) return null;
		String text = control.getText();
		return text;
	}
	
	//! WebViewから文字列を取得
	public static String webview_getTmpText(int index) {
		WebViewItem control = PFInterface.getInstance().m_webList[index];
		if(control == null) return null;
		String tmpText = control.getTmpText();
		return tmpText;
	}

	//! TextBox の位置やサイズ,表示状態,有効/無効を変更
	public static void webview_update(int index, int x, int y, int width, int height, boolean enable, boolean visible) {
		PFInterface pfif = PFInterface.getInstance();
		WebViewItem web = pfif.m_webList[index];
		if(web != null) {
			web.move(x, y, width, height);		
			web.setVisible(visible);
			web.setEnable(enable);
		}
	}

	//! MovieViewの生成
	public static int movieview_create(int x, int y, int width, int height, String defURL, boolean background) {
		
		PFInterface pfif = PFInterface.getInstance();
		GameEngineActivity context = pfif.m_context;
		for(int i = 0; i < pfif.MAX_MOVIE_VIEW; i++) {
			if(pfif.m_movieList[i] == null) {
				MovieViewItem movie = new MovieViewItem(i, context, defURL, x, y, width, height, background);
				pfif.m_movieList[i] = movie;
				if(i > pfif.m_movieListCount) pfif.m_movieListCount = i;
				return i;
			}
		}
		return -1;
	}

	//! MovieViewの破棄
	public static boolean movieview_destroy(int index) {
		PFInterface pfif = getInstance();
		MovieViewItem movie = pfif.m_movieList[index];
		movie.m_remove = true;
		return true;
	}

	//! MovieViewにURLを設定
	public static boolean movieview_setText(int index, String text) {
		final MovieViewItem control = getInstance().m_movieList[index];
		final String inner_text = text;
		if(control == null) return false;
		// 平成25年8月15日(木)
		// EditBoxに習い修正
		PFInterface.getInstance().m_context.runOnUiThread(new Runnable() {
				public void run() {
						control.setText(inner_text);
				}
		});
		return true;
	}
	
	//! MovieBoxから文字列を取得
	public static String movieview_getText(int index) {
		WebViewItem control = PFInterface.getInstance().m_webList[index];
		if(control == null) return null;
		String text = control.getText();
		return text;
	}

	//! MovieBox の位置やサイズ,表示状態,有効/無効を変更
	public static void movieview_update(int index, int x, int y, int width, int height, boolean enable, boolean visible) {
		PFInterface pfif = PFInterface.getInstance();
		MovieViewItem movie = pfif.m_movieList[index];
		if(movie != null) {
			movie.move(x, y, width, height);		
		}
	}
	
	//! MovieView に対するコマンド処理
	public static void movieview_cmd(int index, int cmd) {
		MovieViewItem movie = getInstance().m_movieList[index];
		movie.cmd(cmd);
	}
		
	//-------------------------------------------
	//! Indicatorの生成
	public static int indicator_create(int x, int y, int width, int height, boolean background) {
		
		PFInterface pfif = PFInterface.getInstance();
		GameEngineActivity context = pfif.m_context;
		if(pfif.m_indicator == null)
		{
			IndicatorItem indicator = new IndicatorItem( context, x, y, width, height, background);
			pfif.m_indicator = indicator;
			return 0;
		}
        else
        {
            pfif.m_indicator.setVisible(true);
        }
		return -1;
	}

	//! Indicatorの破棄
	public static boolean indicator_destroy(int index) {
		PFInterface pfif = getInstance();
        if( pfif.m_indicator!=null )
        {
            pfif.m_indicator.m_remove = true;
        }
		return true;
	}

	
	//! IndicatorにURLを設定
	public static boolean indicator_setText(int index, String text) {
		IndicatorItem indicator = getInstance().m_indicator;
		if(indicator == null) return false;
//		indicator.setText(text);
		return true;
	}
	
	//! Indicatorから文字列を取得
	public static String indicator_getText(int index) {
		WebViewItem control = PFInterface.getInstance().m_webList[index];
		if(control == null) return null;
		String text = control.getText();
		return text;
	}

	//! Indicator の位置やサイズ,表示状態,有効/無効を変更
	public static void indicator_update(int index, int x, int y, int width, int height, boolean enable, boolean visible) {
		PFInterface pfif = PFInterface.getInstance();
		IndicatorItem indicator = pfif.m_indicator;
		if(indicator != null) {
			indicator.move(x, y, width, height);		
		}
	}
	
	//! Indicator に対するコマンド処理
	public static void indicator_cmd(int index, int cmd) {
		IndicatorItem indicator = getInstance().m_indicator;
		if(indicator != null) {
            indicator.cmd(cmd);
        }
	}

	//-------------------------------------------
	// メインスレッドから呼ぶ
	public synchronized void updateControl() {
		for(int i = 0; i <= m_textListCount; i++) {
			if(m_textList[i] == null) continue;
			if(m_textList[i].remove()) {
				m_textList[i] = null;
				continue;	// 削除処理対象なら次へ
			}
			m_textList[i].create();	// 生成されたばかりなら、実際の生成処理を行う
			m_textList[i].update(); // 変更内容があるならそこで反映する
		}
		if(m_textListCount >= 0 && m_textList[m_textListCount] == null) {
			int max = -1;
			for(int i = 0; i < m_textListCount; i++) {
				if(m_textList[i] != null) max = i;
			}
			m_textListCount = max;
		}
		// WebView の更新を確認
		for(int i = 0; i <= m_webListCount; i++) {
			if(m_webList[i] == null) continue;
			if(m_webList[i].remove()) {
				m_webList[i] = null;
				continue;	// 削除処理対象なら次へ
			}
			m_webList[i].create();	// 生成されたばかりなら、実際の生成処理を行う
			m_webList[i].update(); // 変更内容があるならそこで反映する
		}
		if(m_webListCount >= 0 && m_webList[m_webListCount] == null) {
			int max = -1;
			for(int i = 0; i < m_webListCount; i++) {
				if(m_webList[i] != null) max = i;
			}
			m_webListCount = max;
		}
		// MovieView の更新を確認
		for(int i = 0; i <= m_movieListCount; i++) {
			if(m_movieList[i] == null) continue;
			if(m_movieList[i].remove()) {
				m_movieList[i] = null;
				continue;	// 削除処理対象なら次へ
			}
			m_movieList[i].create();	// 生成されたばかりなら、実際の生成処理を行う
			m_movieList[i].update(); // 変更内容があるならそこで反映する
		}
		if(m_movieListCount >= 0 && m_movieList[m_movieListCount] == null) {
			int max = -1;
			for(int i = 0; i < m_movieListCount; i++) {
				if(m_movieList[i] != null) max = i;
			}
			m_movieListCount = max;
		}
		// IndicatorView の更新を確認
 
        if( m_indicator!=null )
        {
            if( m_indicator.remove() )
            {
            	m_indicator = null;
            }
            if( m_indicator!=null )
            {
                m_indicator.create();
                m_indicator.update();
            }
        }

	}
	
	//! renderText() で呼び出される、Java側でフォントテクスチャを生成するメソッド。
	public static void drawText(Paint paint, int [] image, int color, int width, int height, float x, float y, String text) {
		paint.setAntiAlias(true);
		paint.setColor(color);
		Bitmap bitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
		//bitmap.setPixels(image, width * (height - 1), -width, 0, 0, width, height);
		bitmap.setPixels(image, 0, width, 0, 0, width, height);
		Canvas canvas = new Canvas(bitmap);
		canvas.drawText(text, x, y, paint);
		//bitmap.getPixels(image, width * (height - 1), -width, 0, 0, width, height);
		bitmap.getPixels(image, 0, width, 0, 0, width, height);
	}
	
	public static long nanotime() {
		return System.nanoTime();
	}
	
	public boolean callInit(int width, int height, String path) {
		m_width = width;
		m_height = height;
		String model = Build.MODEL;
		String brand = Build.BRAND;
		String board = Build.BOARD;
		String version = Build.VERSION.RELEASE;
		String tz = "JST"; // TimeZone.getDefault().toString();
		m_osversion = model + " " + brand + " " + board + " " + version;
		m_tzone = tz;
		boolean result = initSequence(width, height, path, model, brand, board, version, tz);
		m_bexec = true;
		return result;
	}
	
	public void screenRotation(int origin) {
		if(!m_bexec) return;
		int width, height;
		if((origin & 1) == 0) {
			width = (m_width < m_height) ? m_height : m_width;
			height = (m_width > m_height) ? m_height : m_width;
//			width = (m_width < m_height) ? m_width : m_height;
//			height = (m_width > m_height) ? m_width : m_height;
		} else {
			width = (m_width > m_height) ? m_width : m_height;
			height = (m_width < m_height) ? m_width : m_height;

		}
		rotateScreenOrientation(0, width, height);
	}

	public static String generateDeviceIdent() {
		return Build.MANUFACTURER + "`" + Build.MODEL + "`" + ((int)(Math.random() * 16777216));
	}
	
	public static void	billingInit()
	{
		BillingManager.init(getInstance().m_context);
	}

	public static void	billingTerminate()
	{
		BillingManager.requestTerminate();
	}
	
	public static void	billingConsume(String receipt)
	{
		BillingManager.getInstance(getInstance().m_context).requestConsume(receipt);
	}

	public static void	billingGetProducts(String jsonStr)
	{
		Log.d("PFInterface", "json = " + jsonStr);
		List<String> skuList = new ArrayList<String>();
		
		try {
			JSONArray json = new JSONArray(jsonStr);
			int len = json.length();
			
	        for(int i = 0; i < len; ++i) {
	        	skuList.add(json.getString(i));
	        	Log.d("PFInterface", "item = " + json.getString(i));
	        }
		} catch (JSONException e) {
			Log.e("PFInterface", "illegal json string: " + jsonStr);
			return;
		}
		
		BillingManager.getInstance(getInstance().m_context).requestGetProducts(skuList);
	}

	// 課金：購入処理
	public static void billingBuyItem(String sku)
 	{
		BillingManager.getInstance(getInstance().m_context).requestBuy(sku);
 	}
    
    public boolean IsInstallEnd() {
		GameEngineActivity context = getInstance().m_context;
		return context.IsInstallEnd();
	}

    // メーラー起動
    public static void startMailer( String addr , String subject , String body )
    {
    	GameEngineActivity context = getInstance().m_context;
    	context.startExternalApplicationMail( addr , subject , body );
    }

    // アラートダイアログ起動
    public static void startAlertDialog( String title , String message )
    {
    	GameEngineActivity context = getInstance().m_context;
    	context.startAlertDialog( title , message );
    }

	// メーラー起動
    public static void startBrowser( String url )
    {
    	GameEngineActivity context = getInstance().m_context;
    	context.startBrowser( url );
    }
    
    public static int getVersionCode(){
        GameEngineActivity context = getInstance().m_context;
        PackageManager pm = context.getPackageManager();
        int versionCode = 0;
        try{
            PackageInfo packageInfo = pm.getPackageInfo(context.getPackageName(), 0);
            versionCode = packageInfo.versionCode;
        }catch(NameNotFoundException e){
            // placing printStackTrace() because we'll most likely never hit this exception as long as package file is correct
            e.printStackTrace();
        }
        return versionCode;
    }

    public static String getVersionName(){
        GameEngineActivity context = getInstance().m_context;
        PackageManager pm = context.getPackageManager();
        String versionName = "";
        try{
            PackageInfo packageInfo = pm.getPackageInfo(context.getPackageName(), 0);
            versionName = packageInfo.versionName;
        }catch(NameNotFoundException e){
            // placing printStackTrace() because we'll most likely never hit this exception as long as package file is correct
            e.printStackTrace();
        }
        return versionName;
    }
    
    public static void forbidSleep(boolean isForbidden) {
    	GameEngineActivity engineActivity = getInstance().m_context;
    	if (engineActivity != null) {
    		engineActivity.forbidSleep(isForbidden);
    	}
    }

	public native boolean initSequence(int width, int height, String path,
										String model, String brand, String board, String version, String tz);
	public native void frameFlip(int deltaT);
	public native void finishGame();
	public native void inputDeviceKey(int keyId, char eventType);
	public native void inputPoint(int id, int type, int x, int y);
	public native void rotateScreenOrientation(int origin, int width, int height);
	public native void toNativeSignal(int cmd, int param);
	public native int getGLVersion();
    public native void resetViewport();
    public native void onActivityPause();
    public native void onActivityResume();
    public native void WebViewControlEvent(WebView _pWeb, int _flg);
	public native void clientControlEvent(int type, int widget, String data_1, String data_2);
	public native void clientResumeGame();

	static {
		System.loadLibrary("jniproxy");
	}
}
