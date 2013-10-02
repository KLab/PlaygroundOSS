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

import klb.android.GameEngine.PFInterface;
import klb.android.GameEngine.billing.util.IabHelper.OnIabPurchaseFinishedListener;
import klb.android.GameEngine.billing.util.IabResult;
import klb.android.GameEngine.billing.util.Purchase;

/**
 * 
 *  
 * 
 * bikking 課金処理（失敗／成功）インンターフェイス　リスナー
 *
 */
public class IOnIabPurchaseFinishedListener implements OnIabPurchaseFinishedListener {

	private static final String kClassName = IOnIabPurchaseFinishedListener.class.getSimpleName();

	private String sku = null;
	
	private void sendMessageFailed()
	{
		Log.d(kClassName, "sendMessageFailed");
		PFInterface.getInstance().clientControlEvent(
				PFInterface.E_STORE_FAILED, 0, this.sku,"");
	}
	
	private void sendMessagePurchasing()
	{
		Log.d(kClassName, "sendMessagePurchasing");
		PFInterface.getInstance().clientControlEvent(
				PFInterface.E_STORE_PURCHASHING, 0, this.sku, "");
	}
	
	// 購入処理途中の情報をLuaに返す処理を他の場所でも使うので、このインタフェースを公開しておく
	public static void sendMessagePurchased(String sku, Purchase purchase)
	{
		String data_str = purchase.toReceiptString();
		
		// デバッグ：内容確認
		Log.d(kClassName, "Purchased" + sku);
		Log.d(kClassName, "Receipt:\n" + data_str);
	
		PFInterface.getInstance().clientControlEvent(
				PFInterface.E_STORE_PURCHASHED, 0, sku, data_str);
	}
	
	public IOnIabPurchaseFinishedListener(String _sku) {
		
		Log.d(kClassName, "IOnIabPurchaseFinishedListener");
		
		this.sku = _sku;

		sendMessagePurchasing();
	}
	
	private void onIabPurchaseFinishedError(Purchase purchase) {
		// TODO Auto-generated method stub
		Log.d(kClassName, "onIabPurchaseFinishedError");
		// TODO Auto-generated method stub
		sendMessageFailed();
	}


	private void onIabPurchaseFinishedComplete(Purchase purchase) {
		Log.e(kClassName, "onIabPurchaseFinishedComplete");

		IOnIabPurchaseFinishedListener.sendMessagePurchased(this.sku, purchase);
	}
	
	@Override
	public void onIabPurchaseFinished(IabResult result, Purchase purchase) {
		
		Log.d(kClassName, "onIabPurchaseFinished");
		
		if (!result.isSuccess() || result.isFailure() || purchase == null) {
			Log.e(kClassName, "Failure");
			/*
			 * ここに来るパターン:
			 *  - 購入済みで未消費の商品を買おうとした場合
			 *  
			 *  2013/05/23
			 */
			
			onIabPurchaseFinishedError(purchase);
		} else {
			onIabPurchaseFinishedComplete(purchase);
		}
	}

}
