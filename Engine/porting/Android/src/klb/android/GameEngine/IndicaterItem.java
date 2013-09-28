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
import android.view.Gravity;
import android.view.View;
import android.widget.FrameLayout;

class IndicatorItem
{
	private FrameLayout m_layout = null;
	private FrameLayout.LayoutParams m_params = null;
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

    private View m_IndicatorView = null;

	// constructor はGLスレッドから呼ばれる
	public IndicatorItem( GameEngineActivity context,int x, int y, int width, int height, boolean background)
	{
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

        /*
          幅と高さはdefault値を入れておく(適当に100にしておきます)
          小さくは出来るが、大きくは限界がある
          xmlで用意されている大きさが最大でそれ以上は大きく出来ない
        */
        m_width = m_height = 80;
	}
	
	// 値の設定もGLスレッドから呼ばれる
	public void move(int x, int y, int width, int height) {
		m_x = x;
		m_y = y;
		m_width = width;
		m_height = height;
		m_update = true;
	}
			
	private void setStatus()
	{
        if( m_context==null ) return;
        if( m_context.m_IndicatorLayout==null ) return;

		if(m_visible) {
			m_context.m_IndicatorLayout.setVisibility(View.VISIBLE);
		} else {
			m_context.m_IndicatorLayout.setVisibility(View.INVISIBLE);
		}
	}
	// 以下はメインスレッドから呼ばれる(Runnable経由)
	public void create()
	{
		if(m_created) return;

        m_IndicatorView = m_context.getLayoutInflater().inflate(R.layout.indicator, null);
        
		if(m_background)
		{
	        m_params = new FrameLayout.LayoutParams(m_width,m_height);
	        m_params.gravity = Gravity.LEFT|Gravity.TOP;
	        m_params.setMargins(m_x, m_y, m_x+m_width, m_y+m_height);	
			m_context.m_IndicatorLayout.addView(m_IndicatorView,m_params);
		}
		else
		{
			m_layout = new FrameLayout(m_context);
			m_params = new FrameLayout.LayoutParams(m_width, m_height);
			m_params.setMargins(m_x, m_y, 0, 0);
			m_layout.addView(m_IndicatorView, m_params);
			m_context.putControl(m_layout, m_x, m_y, m_x + m_width, m_y + m_height);
		}

        setVisible( true );

		setStatus();
		m_reload = false;
		m_created = true;
	}
	
	public void update()
    {
        if( m_context==null ) return;
        if( m_context.m_IndicatorLayout==null ) return;

		if( m_update )
        {
			if(!m_background)
			{
				if( m_layout!=null )
				{
					m_layout.removeView(m_IndicatorView);
					m_params.width = m_width;
					m_params.height = m_height;
					m_params.setMargins(m_x, m_y, 0, 0);
					m_layout.addView(m_IndicatorView, m_params);
					m_context.replaceView(m_layout, m_x, m_y, m_x + m_width, m_y + m_height);
				}
			}
			setStatus();
		}
		if( cmd_count > 0 ) cmdQueue();
		m_update = false;
	}
	
	public boolean remove()
    {
		if(!m_remove) return false;
		if(null != m_IndicatorView)
		{
			if(m_background) {
				m_context.m_IndicatorLayout.removeView(m_IndicatorView);
			} else {
				m_layout.removeView(m_IndicatorView);
				m_context.removeView(m_layout);
			}
		}
		return true;
	}
	
	public void cmd(int cmd)
    {
		cmdqueue[cmd_count++] = cmd;
	}
	public void cmdQueue()
    {
		if( cmd_count == 0) return;
		for(int i = 0; i < cmd_count; i++)
        {
			cmdProc(cmdqueue[i]);
		}
		cmd_count = 0;
	}
	public void cmdProc(int cmd)
    {
		switch(cmd)
        {
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		}
	}

/*
	public boolean isFinish() {
		if(null == m_indicater_view) return false;
		return m_indicater_view.isFinish();
	}
*/
	
	public void setVisible(boolean visible)
    {
		m_update = true;
		m_visible = visible;
	}

	public void setEnable(boolean enabled)
    {
		m_update = true;
		m_enabled = enabled;
	}

}
