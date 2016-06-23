package com.taller2.matcherapp;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.util.Log;
import android.widget.Toast;

import com.android.volley.AuthFailureError;
import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.VolleyLog;
import com.android.volley.toolbox.JsonObjectRequest;
import com.taller2.matcherapp.app.AppConfig;
import com.taller2.matcherapp.app.AppController;
import com.taller2.matcherapp.helper.Message;
import com.taller2.matcherapp.helper.SQLiteHandler;

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

public class PollingService extends Service {

    public static final String TAG = PollingService.class.getSimpleName();

    // Binder given to clients
    private final IBinder mBinder = new LocalBinder();

    /**
     * Class used for the client Binder.  Because we know this service always
     * runs in the same process as its clients, we don't need to deal with IPC.
     */
    public class LocalBinder extends Binder {
        PollingService getService() {
            // Return this instance of LocalService so clients can call public methods
            return PollingService.this;
        }
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        // Let it continue running until it is stopped.
        Log.d(TAG,"Service started");
        return START_STICKY;
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
    }

    @Override
    public IBinder onBind(Intent intent) {
        return mBinder;
    }

    private void getMessages(){
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
                                String time = message.getString("time");
                                Message msg = new Message(from_id,text,false);
                                saveMessageToMap(msg);
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
                SQLiteHandler db = new SQLiteHandler(getApplicationContext());
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

    public void saveMessageToMap(Message message){

        // Set up the String to be stored: isSelf,text newline
        String isSelf = String.valueOf(message.isSelf());
        String field_sep = ",";
        // TODO length protocol
        String text = message.getMessage();
        String line_sep = "\r\n";
        String data = isSelf+field_sep+text+line_sep;

        String id = message.getFromID();

        String filePath = "data/data/com.taller2.matcherapp/"+id+".txt";
        File file = new File(filePath);
        if (file.exists()){
            try {
                OutputStream fo = new FileOutputStream(file);
                fo.write(data.getBytes());
                fo.close();
                Log.e("Save message","Message saved for conversation with id: "+id);
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        } else {
            Log.e("Save message","Error: there was no file matching for the given id");
        }
    }

}
