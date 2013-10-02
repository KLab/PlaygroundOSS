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

import java.util.Iterator;
import java.util.List;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.util.Log;

import klb.android.GameEngine.PFInterface;
import klb.android.GameEngine.billing.util.IabHelper.QueryInventoryFinishedListener;
import klb.android.GameEngine.billing.util.IabResult;
import klb.android.GameEngine.billing.util.Inventory;
import klb.android.GameEngine.billing.util.Purchase;
import klb.android.GameEngine.billing.util.SkuDetails;
/**
 * 
 *  
 *
 */
public class IQueryInventoryFinishedListener implements QueryInventoryFinishedListener {

	private static final String kClassName = IQueryInventoryFinishedListener.class.getSimpleName();
	
	private List<String> skuList = null;
	
	public IQueryInventoryFinishedListener(List<String> _skuList) {
		Log.d(kClassName, "IQueryInventoryFinishedListener");
		
		this.skuList = _skuList;
	}

	private void onQueryInventoryError() {
		// TODO Auto-generated method stub
		Log.d(kClassName, "onQueryInventoryError");
	}

	private void onQueryInventorySuccess(Inventory inventory) {
		JSONArray resultArray = new JSONArray();
		for(Iterator<String> itr = this.skuList.iterator(); itr.hasNext();) {
			String sku = itr.next();
			
			if (inventory.hasDetails(sku)) {
	 			SkuDetails detail = inventory.getSkuDetails(sku);
				JSONObject obj    = new JSONObject();

				try {
					obj.put("id", detail.getSku());
					obj.put("price", detail.getPrice());
					obj.put("description", detail.getDescription());
					
					/*
					 * Google Playのアプリ名がtitleにくっついてきてしまっているので、
					 * これをそのままクライアントに返すとiOSのtitleの内容と異なってしまう。
					 * なので、()に含まれる文字列を削除する。
					 * アプリ名・商品名設定にはこの点に留意する必要が有る。
					 * GPを考慮した場合、商品名はアプリローカルから取った方がマシかもしれない - 2013/05/23
					 */
					obj.put("title", detail.getTitle().replaceAll("\\([^)]*\\)", "").trim());				
					resultArray.put(obj);
				} catch (JSONException e) {
					Log.e(kClassName, e.toString());
				}
			} else {
				Log.i(kClassName, "Invalid SKU: " + sku);
			}
		}
		
		String resultStr = resultArray.toString();
		
		Log.i(kClassName, "SKU Json: " + resultStr);
		Log.i(kClassName, "length: " + resultStr.length());

		PFInterface.getInstance().clientControlEvent(
				PFInterface.E_STORE_GET_PRODUCTS, 0, resultStr, "");
	}

	@Override
	public void onQueryInventoryFinished(IabResult result, Inventory inventory) {
		Log.d(kClassName, "onQueryInventoryFinished");
		List<String> ownedItem = inventory.getAllOwnedSkus();
		
		for(Iterator<String> itr = ownedItem.iterator(); itr.hasNext();) {
			String sku = itr.next();
			Log.w(kClassName, "Pending(Owned) sku: " + sku);
			
			Purchase pendingPurchase = inventory.getPurchase(sku);
			
			/*
			 * 未消費のアイテムを中断されたトランザクションと見なして、
			 * Luaに購入済み情報である事を返して問い合わせ処理させる。
			 * iOSのporting layerと挙動を合わせるため
			 */
			IOnIabPurchaseFinishedListener.sendMessagePurchased(sku, pendingPurchase);
		}

		if (!result.isSuccess() || result.isFailure()) {
			Log.e(kClassName, "Failure");
			
			onQueryInventoryError();
		} else {
			onQueryInventorySuccess(inventory);
		}
	}
}
