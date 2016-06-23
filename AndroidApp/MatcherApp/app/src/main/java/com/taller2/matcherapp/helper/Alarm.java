package com.taller2.matcherapp.helper;

import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.PowerManager;
import android.util.Log;

import com.android.volley.AuthFailureError;
import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.VolleyLog;
import com.android.volley.toolbox.JsonObjectRequest;
import com.taller2.matcherapp.app.AppConfig;
import com.taller2.matcherapp.app.AppController;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.HashMap;
import java.util.Map;

public class Alarm extends BroadcastReceiver
{
    private static final String TAG = Alarm.class.getSimpleName();

    @Override
    public void onReceive(Context context, Intent intent)
    {
        PowerManager pm = (PowerManager) context.getSystemService(Context.POWER_SERVICE);
        PowerManager.WakeLock wl = pm.newWakeLock(PowerManager.PARTIAL_WAKE_LOCK, "");
        wl.acquire();

        Log.d(TAG,"Getting messages");
        getMessages(context);

        AlarmManager am =( AlarmManager)context.getSystemService(Context.ALARM_SERVICE);
        Intent i = new Intent(context, Alarm.class);
        PendingIntent pi = PendingIntent.getBroadcast(context, 0, i, 0);
        Log.d(TAG,"Alarm set");
        am.setRepeating(AlarmManager.RTC_WAKEUP, System.currentTimeMillis(), 1000 * 10, pi); // Millisec * Second * Minute

        wl.release();
    }

    public void SetAlarm(Context context)
    {
        AlarmManager am =( AlarmManager)context.getSystemService(Context.ALARM_SERVICE);
        Intent i = new Intent(context, Alarm.class);
        PendingIntent pi = PendingIntent.getBroadcast(context, 0, i, 0);
        Log.d(TAG,"Alarm set");
        am.setRepeating(AlarmManager.RTC_WAKEUP, System.currentTimeMillis(), 1000 * 10, pi); // Millisec * Second * Minute
    }

    public void CancelAlarm(Context context)
    {
        Intent intent = new Intent(context, Alarm.class);
        PendingIntent sender = PendingIntent.getBroadcast(context, 0, intent, 0);
        AlarmManager alarmManager = (AlarmManager) context.getSystemService(Context.ALARM_SERVICE);
        alarmManager.cancel(sender);
    }

    private void getMessages(final Context context){
        // Create a GET request, send JSONObject.
        String tag_json_req = "get_new_messages";
        JSONObject json_params = new JSONObject();

        JsonObjectRequest jsonObjReq = new JsonObjectRequest(Request.Method.GET,
                AppConfig.URL_GET_NEW_MESSAGES, json_params,
                new Response.Listener<JSONObject>() {

                    @Override
                    public void onResponse(JSONObject response) {
                        Log.d(TAG, response.toString());
                        try {
                            int count = -1;
                            try {
                                count = Integer.parseInt(response.getString("count"));
                            } catch(NumberFormatException nfe) {
                                System.out.println("Could not parse " + nfe);
                            }
                            if (count <= 0){
                                Log.d(TAG, "El usuario no tiene mensajes nuevos");
                                return;
                            }
                            JSONArray messages = response.getJSONArray("messages");
                            for (int i = 0; i < messages.length(); i++){
                                JSONObject message = messages.getJSONObject(i).getJSONObject("message");
                                String from_id = message.getString("id");
                                String text = message.getString("message");
                                myMessage msg = new myMessage(from_id,text,false);
                                saveMessage(msg);
                            }
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                    }
                }, new Response.ErrorListener() {

            @Override
            public void onErrorResponse(VolleyError error) {
                VolleyLog.d(TAG, "Error: " + error.getMessage());
                Log.d(TAG, error.toString());
            }

        }){
            @Override
            public Map<String, String> getHeaders() throws AuthFailureError {
                // SqLite database handler
                SQLiteHandler db = new SQLiteHandler(context);
                // Fetching user details from sqlite
                HashMap<String, String> user = db.getUserDetails();
                Map<String, String> params = new HashMap<>();
                params.put("Authorization", user.get("token"));
                return params;
            }
        };
        // Adding request to request queue
        AppController.getInstance().addToRequestQueue(jsonObjReq, tag_json_req);
    }

    private void saveMessage(myMessage myMessage){
        // Set up the String to be stored: isSelf,text newline
        String isSelf = String.valueOf(myMessage.isSelf());
        String field_sep = ",";
        // TODO length protocol
        String text = myMessage.getMessage();
        String line_sep = "\r\n";
        String data = isSelf+field_sep+text+line_sep;

        String id = myMessage.getFromID();

        String filePath = "data/data/com.taller2.matcherapp/"+id+".txt";
        File file = new File(filePath);
        try {
            OutputStream fo = new FileOutputStream(file, true);
            fo.write(data.getBytes());
            fo.close();
            Log.e(TAG,"myMessage saved for conversation with id: "+id);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
