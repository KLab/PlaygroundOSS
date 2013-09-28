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
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.View.OnLongClickListener;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.LinearLayout;
import android.content.Context;
import android.graphics.Bitmap;
import java.lang.String;
import java.lang.System;
//import java.lang.Exception;
import java.util.Map;
import java.util.HashMap;
import android.webkit.JavascriptInterface;

class WebViewItem
{
	private Map<String, String> m_extraHeaders = null;
	private LinearLayout m_layout = null;
	private LinearLayout.LayoutParams m_params = null;
//	private WebView m_web = null;
	private HelpWebView m_web = null;
	private String m_url;
	private String m_tmpUrl;
	private String m_consumerKey = null;
	private String m_token = null;
	private int m_x;
	private int m_y;
	private int m_width;
	private int m_height;
	private GameEngineActivity m_context = null;
	private boolean m_nojump;
	public boolean m_created;
	public boolean m_update;
	public boolean m_remove;
	public boolean m_reload;
	public boolean m_visible = true;
	public boolean m_enabled = true;
	public int m_alpha = 0;
	public int m_color = 0xffffff;
	public boolean m_bZoom = true;
	private static int m_nonceSeed = 0;
	private static final String NATIVE_PROTOCOL = "native://";
	
	// class
	public class JsObject
	{
		private Context m_context;
		public JsObject(Context _context) {
			this.m_context = _context;
		}
		
		@JavascriptInterface
		public void cmd(String _str) {
//			int findPos = _str.indexOf("native://");
//			if( findPos < 0 )
//			{
//				return;
//			}
			// native://が見つかったのでコントロールイベントを通知
			m_tmpUrl = _str;//_str.substring(findPos);
			PFInterface.getInstance().WebViewControlEvent(m_web, PFInterface.WEBVIEW_STATUS.E_URLJUMP.GetNum());
		}
	}
	
	// constructor はGLスレッドから呼ばれる
	public WebViewItem(GameEngineActivity context, String url,
						int x, int y, int width, int height,
						String token, String region, String client, String consumerKey,
						String applicationId, String userId,
						String tzone, String version,
						boolean nojump) {

		// カスタマイズヘッダを作る
		m_extraHeaders = new HashMap<String, String>();
		m_extraHeaders.put("API-Model", "straightforward");
		
		if(client != null) m_extraHeaders.put("Client-Version", client);
		if(region != null) m_extraHeaders.put("Region",	region);
		if(applicationId != null) m_extraHeaders.put("Application-ID", applicationId);
		if(userId != null) m_extraHeaders.put("User-ID", userId);
		
		m_extraHeaders.put("OS", "Android");
		m_extraHeaders.put("Time-Zone", tzone);
		m_extraHeaders.put("OS-Version", version);

		m_consumerKey = consumerKey;
		m_token = token;
		
		m_nojump = nojump;

		m_url = url;
		m_x = x;
		m_y = y;
		m_width = width;
		m_height = height;
		m_context = context;
		
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
	
	public String getTmpText() {
		return m_tmpUrl;
	}
	
	public void setText(String text) {
		m_url = text;
		m_reload = true;
	}
	
	private void authHeader() {
		long unixtime = System.currentTimeMillis() / 1000L;
		String auth = "consumerKey=" + m_consumerKey + "&token=" + m_token + "&version=1.1&timeStamp=" + unixtime + "&nonce=WV" + m_nonceSeed;
		m_extraHeaders.remove("authorize");
		m_extraHeaders.put("authorize", auth);
	}
	
	private void setStatus() {
		if(m_visible) {
			m_web.setEnabled(m_enabled);
			m_web.setVisibility(View.VISIBLE);
		} else {
			m_web.setEnabled(false);
			m_web.setVisibility(View.INVISIBLE);
		}
	}
	// 以下はメインスレッドから呼ばれる(Runnable経由)
	public void create() {
		if(m_created) return;
	//	m_web = new WebView(m_context);
		m_web = new HelpWebView(m_context);
		// m_web.getSettings().setJavaScriptEnabled(true);
		
		// ロングタップでの範囲選択off
		m_web.setOnLongClickListener(new OnLongClickListener() {
		@Override
		public boolean onLongClick(View v) {
		    return true;
		}
		});
		m_web.setLongClickable(false);
		
		m_layout = new LinearLayout(m_context);
		m_params = new LinearLayout.LayoutParams(m_width, m_height);
		m_params.setMargins(m_x, m_y, 0, 0);
		
		// 背景色再設定
		setColor(m_alpha, m_color);
		
		// ズーム設定
		setZoom(m_bZoom);
				
		//
		m_layout.addView(m_web, m_params);
		m_layout.setBackgroundColor(0x01FFFFFF);	// αの部分を0にすると黒い画面がでてしまうので、1を入れています　2013.6.20 
		//m_context.putControl(m_layout, m_x, m_y, m_x + m_width, m_y + m_height);
		m_context.putControl(m_layout, m_x, m_y, ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
		
		// authorized header を作る
		authHeader();
//		m_web.setWebChromeClient(new WebChromeClient()
//		{
//		});
		m_web.setWebViewClient(new WebViewClient()
		{
			// 画面更新時のコールバック
			@Override
			public boolean shouldOverrideUrlLoading(WebView webView, String url)
			{
				int native_protocol_begin = url.indexOf(WebViewItem.NATIVE_PROTOCOL);
				if( native_protocol_begin < 0 ) {
					/*
					 * ここでm_nojumpをiOSの挙動に合わせる。
					 * Luaから渡してる間違ったパラメータが既成事実化している模様 
					 */
					//if (!m_nojump) {
					webView.loadUrl(url, m_extraHeaders);
					//}
					return true;
				}

				m_tmpUrl = url.substring(native_protocol_begin + WebViewItem.NATIVE_PROTOCOL.length());
				PFInterface.getInstance().WebViewControlEvent(webView, PFInterface.WEBVIEW_STATUS.E_URLJUMP.GetNum());
				return true;
			}
			
			// ロード開始
			@Override
			public void onPageStarted(WebView view, String url, Bitmap favicon)
			{
				super.onPageStarted(view, url, favicon);
				PFInterface.getInstance().WebViewControlEvent(view, PFInterface.WEBVIEW_STATUS.E_DIDSTARTLOADWEB.GetNum());
			}
			
			// ロードが完了
			@Override
			public void onPageFinished(WebView view, String url)
			{
				super.onPageFinished(view, url);
				PFInterface.getInstance().WebViewControlEvent(view, PFInterface.WEBVIEW_STATUS.E_DIDLOADENDWEB.GetNum());
			}
			
			// ロードがエラー
			@Override
			public void onReceivedError(WebView view, int errorCode, String description, String failingUrl)
			{
				super.onReceivedError(view, errorCode, description, failingUrl);
				PFInterface.getInstance().WebViewControlEvent(view, PFInterface.WEBVIEW_STATUS.E_FAILEDLOADWEB.GetNum());
			}
		});
		
		m_web.getSettings().setJavaScriptEnabled(true);
		m_web.getSettings().setLoadWithOverviewMode(true);
		m_web.getSettings().setUseWideViewPort(true);
        m_web.getSettings().setBuiltInZoomControls(false);
        m_web.setInitialScale(100);
		
		JsObject jsObj = new JsObject(m_context);
		m_web.addJavascriptInterface(jsObj, "eng");
		
		m_web.loadUrl(m_url, m_extraHeaders);
		setStatus();
		m_reload = false;
		m_created = true;
	}
	
	public void update() {
		if(!m_update || m_web == null) return;
		//m_layout.removeView(m_web);
		
		m_params.width = m_width;
		m_params.height = m_height;
		m_params.setMargins(m_x, m_y, 0, 0);
		m_web.requestLayout();
		
		// 背景色再設定
		setColor(m_alpha, m_color);
		
		//m_layout.addView(m_web, m_params);
		//m_context.replaceView(m_layout, m_x, m_y, m_x + m_width, m_y + m_height);
		setStatus();

		if(m_reload) {
			authHeader();
			if(null != m_web) {
				m_web.loadUrl(m_url, m_extraHeaders);
				m_reload = false;
			}
		}
		m_update = false;
	}
	
	public boolean remove() {
		if(!m_remove) return false;
		if(null != m_web) m_context.removeView(m_layout);
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
	
	public void setZoom(boolean _flg)
	{
		m_bZoom = _flg;
		if( m_web == null ) return;
		m_web.getSettings().setBuiltInZoomControls(m_bZoom);
	}
	
	public void setColor(int _alpha, int _color)
	{
		m_alpha = _alpha;
		m_color = _color;
		if( m_web == null ) return;
		int col = (m_alpha << 24) | m_color;
		m_web.setBackgroundColor(col);
	}
	
	public boolean isEqual(WebView _webView) {
		if(m_web != null && m_web == _webView) {
			return true;
		}
		return false;
	}
}


class HelpWebView extends WebView {

    private GestureDetector gestureDetector;
//    private AtomicBoolean mPreventAction = new AtomicBoolean(false);
//    private AtomicLong mPreventActionTime = new AtomicLong(0);
    private boolean mDoubleTouch = false;

    public HelpWebView(Context context) {
        super(context);
        gestureDetector = new GestureDetector(context, new GestureListener());
    }
/*
    public HelpWebView(Context context, AttributeSet attrs) {
        super(context, attrs);
        gestureDetector = new GestureDetector(context, new GestureListener());
    }
*/
/*
    public HelpWebView(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
        gestureDetector = new GestureDetector(context, new GestureListener());
    }
*/
/*
    public HelpWebView(Context context, AttributeSet attrs, int defStyle, boolean privateBrowsing) {
        super(context, attrs, defStyle, privateBrowsing);
        gestureDetector = new GestureDetector(context, new GestureListener());
    }
*/

    @Override
    public boolean onTouchEvent(MotionEvent event) {
    	gestureDetector.onTouchEvent(event);
    	if(mDoubleTouch)
    	{
    		mDoubleTouch = false;
    		return false;
    	}
    	return super.onTouchEvent(event);
/*
        int index = (event.getAction() & MotionEvent.ACTION_POINTER_INDEX_MASK) >> MotionEvent.ACTION_POINTER_INDEX_SHIFT;
        int pointId = event.getPointerId(index);

        // just use one(first) finger, prevent double tap with two and more fingers
        if (pointId == 0){
            gestureDetector.onTouchEvent(event);

            if (mPreventAction.get()){
                if (System.currentTimeMillis() - mPreventActionTime.get() > ViewConfiguration.getDoubleTapTimeout()){
                    mPreventAction.set(false);
                } else {
                    return true;
                }
            }

            return super.onTouchEvent(event);
        } else {
            return true;
        }
*/
    }

    private class GestureListener extends GestureDetector.SimpleOnGestureListener {
        @Override
        public boolean onDoubleTap(MotionEvent e) {
        //    mPreventAction.set(true);
        //    mPreventActionTime.set(System.currentTimeMillis());
            return true;
        }
        @Override
        public boolean onDoubleTapEvent(MotionEvent e) {
        	mDoubleTouch = true;
        //    mPreventAction.set(true);
        //    mPreventActionTime.set(System.currentTimeMillis());
            return true;
        }
    }
}
