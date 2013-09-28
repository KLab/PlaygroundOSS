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
// import klb.android.GameEngine.PFInterface;
import java.lang.String;

import android.view.Gravity;
import android.view.View;
import android.widget.FrameLayout;

class MovieViewItem
{
	private FrameLayout m_layout = null;
	private FrameLayout.LayoutParams m_params = null;
	private MovieView m_video = null;
	private String m_url;
	private int m_index;
	private int m_x;
	private int m_y;
	private int m_width;
	private int m_height;
	private GameEngineActivity m_context = null;
	public boolean m_created;
	public boolean m_update;
	public boolean m_remove;
	public boolean m_reload;
	public boolean m_visible = true;
	public boolean m_enabled = true;
	public boolean m_background = false;
	private int [] cmdqueue = new int [50];
	private int cmd_count = 0;

	// constructor はGLスレッドから呼ばれる
	public MovieViewItem(int index, GameEngineActivity context, String url,
						int x, int y, int width, int height, boolean background) {

		m_index = index;
		m_url = url;
		m_x = x;
		m_y = y;
		m_width = width;
		m_height = height;
		m_context = context;
		m_background = background;
		m_created = false;
		m_update = false;
		m_remove = false;
		m_reload = true;
	}
	
	// 値の設定もGLスレッドから呼ばれる
	public void move(int x, int y, int width, int height) {
		m_x = x;
		m_y = y;
		m_width = width;
		m_height = height;
		m_update = true;
	}
	
	// 値の取得も主にGLスレッドから呼ばれる
	public String getText() {
		return m_url;
	}
	
	public void setText(String text) {
		m_url = text;
		m_reload = true;
	}
		
	private void setStatus() {
		if(m_visible) {
			m_video.setEnabled(m_enabled);
			m_video.setVisibility(View.VISIBLE);
		} else {
			m_video.setEnabled(false);
			m_video.setVisibility(View.INVISIBLE);
		}
	}
	// 以下はメインスレッドから呼ばれる(Runnable経由)
	public void create() {
		if(m_created) return;

		m_video = new MovieView(m_context, m_index);
		if(m_background) {
			m_params = new FrameLayout.LayoutParams(m_width, m_height);
			m_params.gravity = Gravity.CENTER;
			m_params.setMargins(m_x, m_y, 0, 0);
			m_context.m_MovieLayout.addView(m_video,m_params);
		} else {
			m_layout = new FrameLayout(m_context);
			m_params = new FrameLayout.LayoutParams(m_width, m_height);
			m_params.setMargins(m_x, m_y, 0, 0);
			m_layout.addView(m_video, m_params);
			m_context.putControl(m_layout, m_x, m_y, m_x + m_width, m_y + m_height);
		}
		m_video.setMoviePath(m_url);
		setStatus();
		m_reload = false;
		m_created = true;
	}
	
	public void update() {
		if(m_update && m_video != null) {
			if(!m_background) {
				m_layout.removeView(m_video);
				m_params.width = m_width;
				m_params.height = m_height;
				m_params.setMargins(m_x, m_y, 0, 0);
				m_layout.addView(m_video, m_params);
				m_context.replaceView(m_layout, m_x, m_y, m_x + m_width, m_y + m_height);
			}
			setStatus();
			if(m_reload) {
				if(null != m_video) {
					m_video.setMoviePath(m_url);
					m_reload = false;
				}
			}
		}
		if(cmd_count > 0 && m_video != null) cmdQueue();
		m_update = false;
	}
	
	public boolean remove() {
		if(!m_remove) return false;
		if(null != m_video)
		{
			if(m_background) {
				m_context.m_MovieLayout.removeView(m_video);
			} else {
				m_layout.removeView(m_video);
				m_context.removeView(m_layout);
			}
		}
		return true;
	}
	
	public void cmd(int cmd) {
		cmdqueue[cmd_count++] = cmd;
	}
	public void cmdQueue() {
		if(m_video == null || cmd_count == 0) return;
		for(int i = 0; i < cmd_count; i++) {
			cmdProc(cmdqueue[i]);
		}
		cmd_count = 0;
	}
	public void cmdProc(int cmd) {
		if(m_video == null) return;
		switch(cmd) {
		case 0:	// stop
			m_video.stop();
			break;
		case 1:	// play
			m_video.start();
			break;
		case 2:
			m_video.pause();
			break;
		case 3:
			m_video.resume();
			break;
		}
	}
	
	public boolean isFinish() {
		if(null == m_video) return false;
		return m_video.isFinish();
	}
	
	
	public void setVisible(boolean visible) {
		m_update = true;
		m_visible = visible;
	}

	public void setEnable(boolean enabled) {
		m_update = true;
		m_enabled = enabled;
	}

}
