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
import android.content.Context;
import android.graphics.Paint;
import android.text.InputType;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnKeyListener;
import android.view.ViewGroup;
import android.view.inputmethod.InputMethodManager;
import android.text.method.SingleLineTransformationMethod;
import android.util.TypedValue;
import android.widget.EditText;
import java.lang.String;
import android.widget.LinearLayout;
import android.text.InputFilter;

class EditBoxItem
{
	private boolean m_passwdmode = false;
	private LinearLayout m_layout = null;
	private LinearLayout.LayoutParams m_params = null;
	private EditText m_edit = null;
	private String m_text;
	private int m_x;
	private int m_y;
	private int m_width;
	private int m_height;
	private GameEngineActivity m_context = null;
	public boolean m_created;
	public boolean m_update;
	public boolean m_remove;
	public boolean m_visible = true;
	public boolean m_enabled = true;
	public Paint m_Paint = null;
	private String m_hint;
	private int m_gravity;
	private int m_maxlen;

	// constructor はGLスレッドから呼ばれる
	public EditBoxItem(GameEngineActivity context, String text,
						int x, int y, int width, int height, boolean passwdmode) {

		//m_edit = new EditText(context);
		m_edit = null;
		m_passwdmode = passwdmode;

		m_text = text;
		m_x = x;
		m_y = y;
		m_width = width;
		m_height = height;
		m_context = context;
		m_maxlen = 0;
		m_created = false;
		m_update = false;
		m_remove = false;
		
		m_gravity = -1;
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
		if(m_created) {
			return m_edit.getText().toString();
		} else {
			return m_text;
		}
	}
	
	public void setText(String text) {
		m_text = text;
		if(null != m_edit) {
			m_edit.setText(text);
		}
		m_update = true;
	}
	
	private void setStatus() {
		if(m_visible) {
			m_edit.setEnabled(m_enabled);
			m_edit.setVisibility(View.VISIBLE);
		} else {
			m_edit.setEnabled(false);
			m_edit.setVisibility(View.INVISIBLE);
		}
	}
	public void setPaint(Paint paint)
	{
		m_Paint = paint;
	}
	public void setHint(String hint)
	{
		m_hint = hint;
		if(null != m_edit){
			m_edit.setHint(m_hint);
		}
	}

	public void setGravity(int gravity)
	{
		m_gravity = gravity;
		if(null != m_edit){
			m_edit.setGravity(gravity);
		}
	}

	public void setMaxlen(int maxlen)
	{
		if (m_edit != null) {
			if (maxlen > 0) {
				m_edit.setFilters(new InputFilter[] {new InputFilter.LengthFilter(maxlen)});
			} else {
				m_edit.setFilters(new InputFilter[0]); // NO_FILTERS;
			}
		}
		m_maxlen = maxlen;
	}

	// 以下はメインスレッドから呼ばれる(Runnable経由)
	public void create() {
		if(m_created) return;
		m_edit = new EditText(m_context);
        m_edit.setMaxLines(1);
		m_edit.setHint(m_hint);
		setMaxlen(m_maxlen);
		if (m_gravity != -1) {
			m_edit.setGravity(m_gravity);
		}
		if( m_Paint != null ) {
			m_edit.setTypeface(m_Paint.getTypeface());
		}
		// setPaddingしてやらないと文字表示がうまくいかないため  2013/03/21   //
		m_edit.setPadding(10, 0, 10, 0);
		m_edit.setOnKeyListener(new OnKeyListener() {
			@Override
			public boolean onKey(View v, int keyCode, KeyEvent event) {
				if(event.getAction() == KeyEvent.ACTION_DOWN && keyCode == KeyEvent.KEYCODE_ENTER) {
					InputMethodManager inputMethodManager = (InputMethodManager)m_context.getSystemService(Context.INPUT_METHOD_SERVICE);
					inputMethodManager.hideSoftInputFromWindow(v.getWindowToken(), 0);
					return true;
				}
				return false;
			}
		});
		m_edit.setTransformationMethod(SingleLineTransformationMethod.getInstance());
		m_edit.setOnFocusChangeListener(new View.OnFocusChangeListener() {
			@Override
			public void onFocusChange(View v, boolean hasFocus) {
				InputMethodManager inputMethodManager = (InputMethodManager) m_context.getSystemService(Context.INPUT_METHOD_SERVICE);
				if(hasFocus) {
				//	inputMethodManager.showSoftInput(v, InputMethodManager.SHOW_FORCED);
				} else {
					inputMethodManager.hideSoftInputFromWindow(v.getWindowToken(), 0);
				}
				
			}
		});
		if(m_passwdmode) m_edit.setInputType(InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_PASSWORD);

		m_layout = new LinearLayout(m_context);
		m_params = new LinearLayout.LayoutParams(m_width, m_height);
		m_params.setMargins(m_x, m_y, 0, 0);
		m_layout.addView(m_edit, m_params);
		//m_context.putControl(m_layout, m_x, m_y, m_x + m_width, m_y + m_height);
		m_context.putControl(m_layout, m_x, m_y, ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
		m_edit.setText(m_text);
		
		setStatus();
		m_created = true;
	}
	
	public void update() {
		if(!m_update || m_edit == null) return;
		//m_layout.removeView(m_edit);

		if( m_Paint != null )
		{
			float textSize = m_Paint.getTextSize();
			m_edit.setTextSize(TypedValue.COMPLEX_UNIT_PX, textSize);
			int tmpHeight = (int)(textSize * 2.0f);
			if(m_height < tmpHeight)
			{
				m_height = tmpHeight;
			}
		}

		m_params.width = m_width;
		m_params.height = m_height;
		m_params.setMargins(m_x, m_y, 0, 0);
		m_edit.requestLayout();
		//m_layout.addView(m_edit, m_params);
		//m_context.replaceView(m_layout, m_x, m_y, m_x + m_width, m_y + m_height);
		setStatus();
		m_text = m_edit.getText().toString();
		m_update = false;
	}
	
	public boolean remove() {
		if(!m_remove) return false;
		if(m_edit != null) m_context.removeView(m_layout);
		return true;
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
