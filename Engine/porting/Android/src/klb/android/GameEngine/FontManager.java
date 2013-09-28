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

import android.content.res.AssetManager;
import android.graphics.Paint;

public class FontManager 
{
	private static FontManager instance = new FontManager();	// インスタンス実体はこのメンバ
	
	/*!
	 * @brief	コンストラクタ
	 */
	private FontManager() {}
	
	/*!
	 * @brief	インスタンス取得
	 */
	public static FontManager getInstance() {
		return instance;
	}
	
	/*!
	 * @brief	Paint作成
	 */
	static Paint 		renderTarget = null;
	static AssetManager	mgrAsset	 = null;
	static String		lastFont	 = null;
	
	public static Paint CreatePaint( String _fntName )
	{
		String fntName = _fntName;
		
		if (renderTarget == null) {
			renderTarget = new Paint();
		}
		if ( fntName==null ) return renderTarget;
		
		boolean refresh = false;
		if ( lastFont==null ) {
			lastFont = fntName;
			refresh = true;
		} else {
			if (lastFont.equals(fntName) == false) {
				lastFont = fntName;
				refresh = true;
			}
		}
		
		if (mgrAsset == null) {
			mgrAsset = GameEngineActivity.GetAssetManager();
			refresh = true;
		}
		
		if (refresh) {
			try {
				// ファイルの存在チェック
				mgrAsset.open( fntName );
				
				// 指定のフォントを作成して設定
				renderTarget.setTypeface( Typefaces.get(mgrAsset, fntName) );
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		
		return renderTarget;
	}
	
	public static void setTextSize( Paint _paint, float _size )
	{
		if( _paint == null ) return;
		_size = _size * 5.0f / 6.0f; // TODO：iOSでもやってる魔法の呪文・・・何だろう
		_paint.setTextSize(_size);
	}
	
	public static void setAntiAlias( Paint _paint, boolean _bAlias )
	{
		if( _paint == null ) return;
		_paint.setAntiAlias( _bAlias );
	}
	
	public static float measureText( Paint _paint, String _str )
	{
		if( _paint == null ) return 0.0f;
		return _paint.measureText( _str );
	}
	
	public static Paint.FontMetrics getFontMetrics( Paint _paint )
	{
		if( _paint == null ) return null;
		return _paint.getFontMetrics();
	}
}
