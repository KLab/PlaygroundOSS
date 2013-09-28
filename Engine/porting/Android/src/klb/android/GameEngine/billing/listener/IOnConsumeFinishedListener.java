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

import klb.android.GameEngine.billing.util.IabHelper.OnConsumeFinishedListener;
import klb.android.GameEngine.billing.util.IabResult;
import klb.android.GameEngine.billing.util.Purchase;


/**
 * 
 *  
 *
 */
public class IOnConsumeFinishedListener implements OnConsumeFinishedListener {

	private static final String kClassName = IOnConsumeFinishedListener.class.getSimpleName();
	
	//private BillingManager billingManager = null;
	Purchase purchase = null;
	public IOnConsumeFinishedListener(Purchase _purchase) {
		
		Log.d(kClassName, "IOnConsumeFinishedListener");
		
		this.purchase = _purchase;
	}

	private void onConsumeFinishedError(IabResult result, Purchase purchase) {
		Log.e(kClassName, "onConsumeFinishedError: " + result.toString());
		
		// oh hell.. we are doomed. try again disparately?
	}

	private void onConsumeFinishedSuccess(Purchase purchase) {
		Log.e(kClassName, "onConsumeFinishedSuccess: " + purchase.toString());
		// 消費終了お疲れさま 
	}

	
	@Override
	public void onConsumeFinished(Purchase purchase, IabResult result) {
		
		Log.d(kClassName, "onConsumeFinished");
		
		if (!result.isSuccess() || result.isFailure()) {
			Log.e(kClassName, "Failure: " + result.toString());
			
			onConsumeFinishedError(result, purchase);
		} else {
			onConsumeFinishedSuccess(purchase);
		}
	}
}
