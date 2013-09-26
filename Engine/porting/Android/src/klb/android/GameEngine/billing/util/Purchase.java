/* Copyright (c) 2012 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package klb.android.GameEngine.billing.util;

import org.json.JSONException;
import org.json.JSONObject;

import android.util.Log;

/**
 * Represents an in-app billing purchase.
 */
public class Purchase {
    String mOrderId;
    String mPackageName;
    String mSku;
    long mPurchaseTime;
    int mPurchaseState;
    String mDeveloperPayload;
    String mToken;
    String mOriginalJson;
    String mSignature;
    
    public static Purchase fromReceiptString(String receiptString) {    	
	    try {
	    	JSONObject o = new JSONObject(receiptString);
	    	String signature = o.getString("signature");
	    	String jsonPurchaseInfo = new String(Base64.decode(o.getString("data")));
	    	
	    	return new Purchase(jsonPurchaseInfo, signature);
	    } catch (Base64DecoderException e) {
	        Log.e("Purchase", e.toString());
	        return null;
	    } catch (JSONException e) {
	    	Log.e("Purchase", e.toString());
	    	return null;
	    }
    }

    public Purchase(String jsonPurchaseInfo, String signature) throws JSONException {
        mOriginalJson = jsonPurchaseInfo;
        JSONObject o = new JSONObject(mOriginalJson);
        mOrderId = o.optString("orderId");
        mPackageName = o.optString("packageName");
        mSku = o.optString("productId");
        mPurchaseTime = o.optLong("purchaseTime");
        mPurchaseState = o.optInt("purchaseState");
        mDeveloperPayload = o.optString("developerPayload");
        mToken = o.optString("token", o.optString("purchaseToken"));
        mSignature = signature;
    }

    public String getOrderId() { return mOrderId; }
    public String getPackageName() { return mPackageName; }
    public String getSku() { return mSku; }
    public long getPurchaseTime() { return mPurchaseTime; }
    public int getPurchaseState() { return mPurchaseState; }
    public String getDeveloperPayload() { return mDeveloperPayload; }
    public String getToken() { return mToken; }
    public String getOriginalJson() { return mOriginalJson; }
    public String getSignature() { return mSignature; }

    public String toReceiptString() {
    	JSONObject obj    = new JSONObject();
    	
    	try {
	    	obj.put("signature", mSignature);
	    	obj.put("data", Base64.encode(mOriginalJson.getBytes()));
    	} catch (JSONException e) {
    		Log.e("Purchase", "Could not generate receiptString: " + e.toString());
    	}
    	return obj.toString();
    }
}
