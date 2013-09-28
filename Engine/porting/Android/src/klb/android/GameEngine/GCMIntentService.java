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

import java.util.Iterator;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import com.google.android.gcm.GCMBaseIntentService;

public class GCMIntentService extends GCMBaseIntentService
{
	/*
	 * コンストラクタ
	 */
	public GCMIntentService() {
		super(Integer.toString(R.string.sender_id));
	}
	
	/*
	 * GCMサーバへの登録完了時の処理
	 * @see com.google.android.gcm.GCMBaseIntentService#onRegistered(android.content.Context, java.lang.String)
	 */
	@Override
    protected void onRegistered(Context context, String registrationId) {
    }
	
	/*
	 * GCMサーバからの登録解除完了時の処理
	 * @see com.google.android.gcm.GCMBaseIntentService#onUnregistered(android.content.Context, java.lang.String)
	 */
	@Override
	protected void onUnregistered(Context arg0, String arg1) {
	}   

	/*
	 * メッセージ到着時の処理
	 * @see com.google.android.gcm.GCMBaseIntentService#onMessage(android.content.Context, android.content.Intent)
	 */
    @Override
    protected void onMessage(Context context, Intent intent)
    {
    	showNotification( context, intent );
    	/*
    	Bundle messageBundle = intent.getExtras(); // Intent#getExtras() で受信したメッセージの内容を取得

        // キー・バリュー形式のメッセージにBundleとしてアクセス
        Iterator<String> iterator = messageBundle.keySet().iterator();
        while (iterator.hasNext()) {
            String key = iterator.next();
            // 取得したキー・バリューの対をログ出力
            Log.d(TAG, key + " = " + messageBundle.getString(key));
        }
        try {
            showNotification(context,
                    URLDecoder.decode(messageBundle.getString("message"), "UTF-8"),
                    URLDecoder.decode(messageBundle.getString("detail"), "UTF-8"));
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
        */
    }

    /*
     * エラー時の処理
     * @see com.google.android.gcm.GCMBaseIntentService#onError(android.content.Context, java.lang.String)
     */
	@Override
	protected void onError(Context arg0, String arg1) {
	}
    
    /*
     * NotificationManagerを使って、受信したメッセージの内容を表示
     */
    private void showNotification(Context _context, Intent _intent)
    {
    	Bundle messageBundle = _intent.getExtras(); // Intent#getExtras() で受信したメッセージの内容を取得
    	
    	Iterator<String> iterator = messageBundle.keySet().iterator();
    	Log.d(TAG, "-----------------------------");
    	Log.d(TAG, "  GCM Message");
    	Log.d(TAG, "-----------------------------");
        while (iterator.hasNext())
        {
            String key = iterator.next();
            // 取得したキー・バリューの対をログ出力
            Log.d(TAG, key + " = " + messageBundle.getString(key));
        }
        Log.d(TAG, "-----------------------------");
        
        String message_title = _context.getString(R.string.app_name);
        String message_detail = _intent.getStringExtra("message");
        
        Intent intent = new Intent( _context, GameEngineActivity.class );
        intent.setFlags( Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_SINGLE_TOP );
        PendingIntent contentIntent = PendingIntent.getActivity( _context, 0, intent, 0 );
        
        int icon = R.drawable.ic_launcher;  // TODO : change icon
        long when = System.currentTimeMillis();
		long[] vibrates = {0, 100, 200, 300};
        Notification notification = new Notification( icon, message_detail, when );
        notification.setLatestEventInfo( _context, message_title, message_detail, contentIntent );
		notification.defaults |= Notification.DEFAULT_VIBRATE | Notification.DEFAULT_LIGHTS;
		notification.flags |= Notification.FLAG_AUTO_CANCEL | Notification.FLAG_SHOW_LIGHTS;
		notification.ledARGB = 0xff00ff00;
		notification.ledOnMS = 10000;
		notification.ledOffMS = 300;
		notification.vibrate = vibrates;

		NotificationManager notificationManager = (NotificationManager)_context.getSystemService(Context.NOTIFICATION_SERVICE); 
		notificationManager.notify(R.string.app_name, notification);
    }
}
