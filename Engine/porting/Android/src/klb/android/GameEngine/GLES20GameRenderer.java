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

import klb.android.GameEngine.GameEngineActivity;
import klb.android.GameEngine.PFInterface;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import java.lang.Runnable;
import java.lang.String;
import android.opengl.GLSurfaceView;
import android.os.SystemClock;
import android.util.Log;

public class GLES20GameRenderer implements GLSurfaceView.Renderer {
	private static String FILE_PATH = null;	// ファイルパス
	private static boolean mBInitialize = false;
	private GameEngineActivity mContext = null;
	private long mPreTime;
	private int m_Width;
	private int m_Height;

	public GLES20GameRenderer(GameEngineActivity context, String path) {
		mContext = context;
		mPreTime = SystemClock.uptimeMillis();
		FILE_PATH = path;
		runCtrl = new Runnable() {
			@Override
			public void run() {
				PFInterface.getInstance().updateControl();
			}
		};
	}

	Runnable runCtrl = null;
	
	@Override
	public void onDrawFrame(GL10 glUnused) {
		// 直前のフレーム呼び出しからの経過時間をミリ秒単位で求め、フレーム処理に渡す。
		long nowTime = SystemClock.uptimeMillis();
		int deltaT = (mPreTime != 0) ? (int)(nowTime - mPreTime) : 1;
		mPreTime = nowTime;	// 今回取得した時刻が、次回計算時の基準となる。
		PFInterface pfif = PFInterface.getInstance();
		if(deltaT > 7000) {
			Log.d("Cpp", "long time frame!!");
		}
		
		// インストール処理を別スレッドで行うことになったため  2013/04/22  
		if(mContext.IsInstallEnd() == false)
		{
			return;
		}
		
		// onSurfaceChangedから移植  2013/04/22  
		// 最初のコールでマルチプラットフォームエンジンの初期化シーケンスを呼び出す。
    	if(!mBInitialize) {
    		PFInterface.getInstance().callInit(m_Width, m_Height, FILE_PATH);
    		mBInitialize = true;	// 二回目以降は呼び出さない。
    	}
   	
    	if(mContext.IsUsePause() == true)
    	{
    		PFInterface.getInstance().clientResumeGame();
    		mContext.SetUsePause(false);
    	}

		pfif.frameFlip(deltaT);	// C++ のフレーム処理が呼ばれる。

		// OS によるコントロールの処理を行う。
		mContext.runOnUiThread(runCtrl);
	}
	
    @Override
	public void onSurfaceChanged(GL10 glUnused, int width, int height) {
        // Ignore the passed-in GL10 interface, and use the GLES20
        // class's static methods instead.
        //        GLES20.glViewport(0, 0, width, height);

        // ビューポート設定をスケーリングさせたのに再設定
        //		PFInterface pfif = PFInterface.getInstance();
        //		pfif.resetViewport();

        // 上記でビューポートを設定していたから再設定が必要だった。ゲーム内で設定しているのだからここで設定する必要は無いはず。
    	
    	// インストール処理を別スレッドで行うことになった関係で下記をpublic void onDrawFrame(GL10 glUnused)に移動します  2013/04/22  
    	m_Width = width;
    	m_Height = height;
/*
    	// 最初のコールでマルチプラットフォームエンジンの初期化シーケンスを呼び出す。
    	if(!mBInitialize) {
    		PFInterface.getInstance().callInit(width, height, FILE_PATH);
    		mBInitialize = true;	// 二回目以降は呼び出さない。
    	}
*/
    }
 
    @Override
	public void onSurfaceCreated(GL10 glUnused, EGLConfig config) {
    }
 
    public void resetPreTime() {
    	mPreTime = 0;
    }
    
    // 再開された時、再開時点を元に deltaT を求められるようにしておく。
    public void onRestart() {
    	mPreTime = SystemClock.uptimeMillis();
    }
}
