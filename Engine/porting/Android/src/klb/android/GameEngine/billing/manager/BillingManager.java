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
package klb.android.GameEngine.billing.manager;

import java.util.List;

import klb.android.GameEngine.PFInterface;

import klb.android.GameEngine.billing.util.IabHelper;
import klb.android.GameEngine.billing.util.Purchase;

import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;

import android.app.Activity;
import android.content.Intent;
import android.util.Log;

import klb.android.GameEngine.billing.listener.IOnIabSetupFinishedListener;
import klb.android.GameEngine.billing.listener.IQueryInventoryFinishedListener;
import klb.android.GameEngine.billing.listener.IOnConsumeFinishedListener;
import klb.android.GameEngine.billing.listener.IOnIabPurchaseFinishedListener;
/**
 * 
 *  
 *
 */
public class BillingManager {
	
	private static final String kClassName = BillingManager.class.getSimpleName();
	
	private Activity activity = null;
	private IabHelper iabHelper = null;
	private static BillingManager billingManager = null;

	public static BillingManager getInstance(Activity context) {
		BillingManager.init(context);
		return billingManager;
	}
	
	private boolean isBillingAvailable() {
		/*
		 *  Manifestが正しく設定されていてもIntentが使えない状況が存在する:
		 *   - 端末初期化後に一度もGoogle Playを開いてない状態でapkをadb installして起動した場合
		 *
		 *  2013/5/23
		 */
		
	    final PackageManager packageManager = this.activity.getPackageManager();
	    final Intent intent = new Intent("com.android.vending.billing.InAppBillingService.BIND");
	    List<ResolveInfo> list = packageManager.queryIntentServices(intent, 0);
	    return list.size() > 0;
	}
	
	private BillingManager(Activity context) {
		Log.d(kClassName, "BillingManager");
		
		this.activity  = context;
		this.iabHelper = new IabHelper(this.activity);
		
		this.iabHelper.enableDebugLogging(true); // TODO : Production is false : Debug is true
		
		if (!isBillingAvailable()) {
			PFInterface.startAlertDialog("課金制限", "Google Playアカウントを確認してください");
		} else {
			this.iabHelper.startSetup(new IOnIabSetupFinishedListener());
		}
	}
	
	// INIT
	public static void init(Activity context) {
		if (billingManager == null)  {
			billingManager = new BillingManager(context);
		}
		
		//Handler handler = new Handler();
	}
	// GET_PRODUCTS
	public void requestGetProducts(List<String> skuList) {
		this.iabHelper.queryInventoryAsync(
				true,
				skuList,
				new IQueryInventoryFinishedListener(skuList));
	}

	// FINISH_TRANSACTION
	public void requestConsume(String receipt) {
		Purchase purchase = Purchase.fromReceiptString(receipt);
		this.iabHelper.consumeAsync(
				purchase,
				new IOnConsumeFinishedListener(purchase));
	}
	
	// BUY_ITEM
	public void requestBuy(String sku) {
		int requestCode = 4649;
		this.iabHelper.launchPurchaseFlow(
				sku,
				requestCode,
				new IOnIabPurchaseFinishedListener(sku));
	}

	// RELEASE
	public static void requestTerminate()
	{
		if (billingManager != null) {
			if (billingManager.iabHelper != null){
				billingManager.iabHelper.dispose();
				billingManager.iabHelper = null;
			}
			billingManager = null;
		}
	}
	
	public boolean onActivityResult(int requestCode, int resultCode, Intent data)
	{
		return this.iabHelper.handleActivityResult(requestCode, resultCode, data);
	}

}
