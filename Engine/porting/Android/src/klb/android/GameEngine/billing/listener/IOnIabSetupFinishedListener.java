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
package klb.android.GameEngine.billing.listener;

import android.util.Log;

import klb.android.GameEngine.billing.util.IabHelper.OnIabSetupFinishedListener;
import klb.android.GameEngine.billing.util.IabResult;

/**
 * 
 *  
 * 
 * billing setup 終了処理（失敗／成功）　インターフェイス　リスナー
 *
 */
public class IOnIabSetupFinishedListener implements OnIabSetupFinishedListener {

	private static final String kClassName = IOnIabSetupFinishedListener.class.getSimpleName();

	public IOnIabSetupFinishedListener() {
		Log.d(kClassName, "IOnIabSetupFinishedListener");
	}
	
	@Override
	public void onIabSetupFinished(IabResult result) {

		Log.d(kClassName, "onIabSetupFinished");
	}

}
