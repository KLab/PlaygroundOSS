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
//import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

public class GameGLSurfaceView extends GLSurfaceView {
	static final int TOUCH_MAX = 10;
	GLES20GameRenderer mRenderer;
	private int [] touch_id = new int [TOUCH_MAX];
	private int [] touch_x = new int [TOUCH_MAX];
	private int [] touch_y = new int [TOUCH_MAX];
	private int touch_alloc_cursor = 0;
	private GameEngineActivity context;

    public GameGLSurfaceView(GameEngineActivity context, String path) {
    	super(context);
    	this.context = context;
        for(int i = 0; i < TOUCH_MAX; i++) touch_id[i] = -1;
        PFInterface pfif = PFInterface.getInstance();
        int glver = pfif.getGLVersion();	// nativeがビルド対象としているGLのバージョンを取得
        setEGLContextClientVersion(glver);
        // setEGLContextClientVersion(1);	// use OpenGL ES 1.1
        // setEGLContextClientVersion(2);	// use OpenGL ES 2.0
        mRenderer = new GLES20GameRenderer(context, path);
        setRenderer(mRenderer);
    }
    
    public void onRestart()
    {
		TouchClear();
    	// mRenderer.onRestart();
    	mRenderer.resetPreTime();
    }
    
    @Override
	public void onPause()
    {
		TouchClear();
    	PFInterface pfif = PFInterface.getInstance();
    	pfif.onActivityPause();
    	
    	mRenderer.resetPreTime();
    }
    
    @Override
	public void onResume()
    {
		TouchClear();
    	PFInterface pfif = PFInterface.getInstance();
    	pfif.onActivityResume();
    	
    	mRenderer.resetPreTime();
    }
    
    @Override
	public boolean onTouchEvent(MotionEvent ev) {
    	PFInterface pfif = PFInterface.getInstance();
        
        // データコピー処理時のインジケータを表示するため、かなり無理めな実装となり、
    	// PFInterface.getInstance().callInit(m_Width, m_Height, FILE_PATH);
    	// が呼ばれるのがデータ終了後となっているため下記処理追加  2013/05/09  
        if(pfif.IsInstallEnd() == false) return true;
  
        float x;
        float y;

        switch(ev.getActionMasked())
        {
        default:
        	
        	break;
        case MotionEvent.ACTION_DOWN:
        {
        	// 同時押しなら、押された分全てを送る
        	int count = ev.getPointerCount();
        	for(int i = 0; i < count; i++) {
        		int id = -1;
        		for(int j = 0; j < TOUCH_MAX; j++) {
        			int cursor = (touch_alloc_cursor + j) % TOUCH_MAX;
        			if(touch_id[cursor] < 0) {
        				id = cursor;
        				touch_alloc_cursor = (cursor + 1) % TOUCH_MAX;
        				break;
        			}
        		}
        		if(id < 0) break;	// idが割り当てられない
        		touch_id[id] = ev.getPointerId(i);
        		x = ev.getX(i);
        		y = ev.getY(i);
        		touch_x[id] = (int)x;
        		touch_y[id] = (int)y;
        		pfif.inputPoint(id, PFInterface.E_INPUT_TYPE_CLICK, (int)x, (int)y);
        	}
        }
        break;
        case MotionEvent.ACTION_POINTER_DOWN:
        {
        	// 変化のあった pointer についてのみ送る
            int index = ev.getActionIndex();
       		int jid = ev.getPointerId(index);
       		int id = -1;
        	for(int j = 0; j < TOUCH_MAX; j++) {
                int cursor = (touch_alloc_cursor + j) % TOUCH_MAX;
       			if(touch_id[cursor] < 0) {	// 最初に見つけたブランク候補
       				id = cursor;
        			touch_alloc_cursor = (cursor + 1) % TOUCH_MAX;
       				break;
       			}
       		}
       		if(id < 0) break;	// idが割り当てられない
       		touch_id[id] = jid;
       		x = ev.getX(index);
       		y = ev.getY(index);
       		touch_x[id] = (int)x;
       		touch_y[id] = (int)y;
       		pfif.inputPoint(id, PFInterface.E_INPUT_TYPE_CLICK, (int)x, (int)y);
        }
        break;
        case MotionEvent.ACTION_MOVE:
        {
        	// 同時押しなら、押された分全てを送る
        	int count = ev.getPointerCount();
        	for(int i = 0; i < count; i++) {
        		int jid = ev.getPointerId(i);
        		int id = -1;
        		for(int j = 0; j < TOUCH_MAX; j++) {
        			if(jid == touch_id[j]) {
        				id = j;
        				break;
        			}
        		}
        		if(id < 0) break;	// 該当するIDのタッチが見つからなかった
        		x = ev.getX(i);
        		y = ev.getY(i);
        		if((int)x != touch_x[id] || (int)y != touch_y[id]) {
        			// move はポインタが動いた場合のみ通知する
        			touch_x[id] = (int)x;
        			touch_y[id] = (int)y;
        			pfif.inputPoint(id, PFInterface.E_INPUT_TYPE_DRAG, (int)x, (int)y);
        		}
        	}
        }
        break;
        case MotionEvent.ACTION_POINTER_UP:
        {
            int index = ev.getActionIndex();
        	int jid = ev.getPointerId(index);
        	int id = -1;
    		for(int j = 0; j < TOUCH_MAX; j++) {
    			if(jid == touch_id[j]) {
    				id = j;
    				break;
    			}
    		}
    		if(id < 0) break;	// 該当するIDのタッチが見つからなかった
    		x = ev.getX(index);
    		y = ev.getY(index);
    		touch_id[id] = -1;
    		pfif.inputPoint(id, PFInterface.E_INPUT_TYPE_RELEASE, (int)x, (int)y);
        }
        break;
        case MotionEvent.ACTION_UP:
        {
        	int count = ev.getPointerCount();
        	for(int i = 0; i < count; i++) {
        		int jid = ev.getPointerId(i);
        		int id = -1;
        		for(int j = 0; j < TOUCH_MAX; j++) {
        			if(jid == touch_id[j]) {
        				id = j;
        				break;
        			}
        		}
        		if(id < 0) break;	// 該当するIDのタッチが見つからなかった
        		x = ev.getX(i);
        		y = ev.getY(i);
        		touch_id[id] = -1;
        		pfif.inputPoint(id, PFInterface.E_INPUT_TYPE_RELEASE, (int)x, (int)y);
        	}
        }
        break;
        case MotionEvent.ACTION_CANCEL:
        {
        	int count = ev.getPointerCount();
        	for(int i = 0; i < count; i++) {
        		int jid = ev.getPointerId(i);
        		int id = -1;
        		for(int j = 0; j < TOUCH_MAX; j++) {
        			if(jid == touch_id[j]) {
        				id = j;
        				break;
        			}
        		}
        		if(id < 0) break;	// 該当するIDのタッチが見つからなかった
        		x = ev.getX(i);
        		y = ev.getY(i);
        		pfif.inputPoint(id, PFInterface.E_INPUT_TYPE_RELEASE, (int)x, (int)y);	// release
        	}
        }
        break;
    	}
        context.refreshSystemUi();
    	return true; // super.onTouchEvent(ev);
    }
	
	private void TouchClear()
	{
		PFInterface pfif = PFInterface.getInstance();
		for( int i=0 ; i<TOUCH_MAX ; i++ )
		{
			int id = touch_id[i];
			if(id >= 0) {
				pfif.inputPoint(id, PFInterface.E_INPUT_TYPE_RELEASE, touch_x[id], touch_y[id]);	// release
			}
			touch_id[i] = -1;
			touch_x[i] = touch_y[i] = 0;
		}
	}
}
