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

import java.io.FileInputStream;
import java.io.IOException;

import android.content.Context;
import android.media.MediaPlayer;
import android.view.SurfaceView;
import android.view.SurfaceHolder;

class MovieView extends SurfaceView
	implements SurfaceHolder.Callback, MediaPlayer.OnCompletionListener {
	private int m_index;
	private MediaPlayer mp = null;
	private String mPath = null;
	private boolean playing = false;
	private boolean pause = false;
	private boolean finished = false;
	private boolean m_bWaitPlayerCreated = false;
    private int m_current = 0;  // 2013.1.29  途中からの再生に対応
	
	public MovieView(Context context, int index) {
		super(context);
		m_index = index;
		setZOrderOnTop(true);	// GLSurfaceView より手前に表示しなければならないため。
		SurfaceHolder holder = getHolder();
		holder.addCallback(this);
		holder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
	}

	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
		
	}

	public boolean setMoviePath(String path) {
		try {
			if(mp != null) {
				FileInputStream fis = null;
				fis = new FileInputStream(path);
				if( fis != null ) 
				{
					mp.setDataSource(fis.getFD());
					mp.prepare();
					fis = null;
				}
			}
			mPath = path;
			return true;
		} catch(IllegalArgumentException e) {
			e.printStackTrace();
			return false;
		} catch(IOException e) {
			e.printStackTrace();
			return false;
		}
	}

	public boolean start() {
		if( mp != null )
		{
			// 既に再生中の場合は再生位置を先頭に戻す
			if( playing ) {
				mp.seekTo(m_current);  // 2013.1.29  途中からの再生に対応
			}
			mp.start();
			playing = true;
			finished = false;
			return true;
		}
		else
		{
			// まだMediaPlayerが作成されていないので作成待ちフラグをあげる
			m_bWaitPlayerCreated = true;
		}
		return false;
	}
	
	public boolean stop() {
		if( mp != null && playing == true )
		{
			mp.stop();
			playing = false;
			pause = false;
			return true;
		}
		return false;
	}
	
	public boolean pause() {		
		if( playing == true && pause == false) 
		{
			if(mp != null) mp.pause();
			pause = true;
			return true;
		}
		return false;
	}
	
	public boolean resume() {
		if( mp != null && playing == true && pause == true )
		{
			mp.start();
			pause = false;
			return true;
		}
		return false;
	}
	
	@Override
	public void surfaceCreated(SurfaceHolder holder) {
		try {
            if( mp==null )
            {
                mp = new MediaPlayer();
                mp.setDisplay(holder);
                mp.setOnCompletionListener(this);
                if(mPath != null) {
                    setMoviePath(mPath);
                }
                if( m_bWaitPlayerCreated )
                {
                    start();
                    m_bWaitPlayerCreated = false;

                    if(pause) mp.pause();
                }
                else
                {
                    start();
                }
            }
		} catch(IllegalArgumentException e) {
			e.printStackTrace();
		} catch(IllegalStateException e) {
			e.printStackTrace();
		}
	}
	
	public boolean isFinish() { return finished; }
	
	// 終了時に呼ばれる
	@Override
	public void onCompletion(MediaPlayer mediaPlayer) {
		mp.pause();
		playing = false;
		pause = false;
		finished = true;

		// 終了をnative側に通知する
		PFInterface.getInstance().toNativeSignal(PFInterface.MOVIE_FINISHED, m_index);
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		if(mp != null) {
            m_current = mp.getCurrentPosition();
			mp.release();
			mp = null;
		}
	}
}
