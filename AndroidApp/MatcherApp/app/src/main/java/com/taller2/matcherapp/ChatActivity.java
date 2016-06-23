package com.taller2.matcherapp;

import android.app.ProgressDialog;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;

import com.android.volley.AuthFailureError;
import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.VolleyLog;
import com.android.volley.toolbox.JsonObjectRequest;
import com.taller2.matcherapp.app.AppConfig;
import com.taller2.matcherapp.app.AppController;
import com.taller2.matcherapp.helper.Alarm;
import com.taller2.matcherapp.helper.CustomListAdapter;
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
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

public class ChatActivity extends AppCompatActivity {

    private final static String TAG = ChatActivity.class.getSimpleName();
    private ProgressDialog pDialog;
    Alarm alarm = new Alarm();
    SQLiteHandler db = new SQLiteHandler(this);
    ScheduledExecutorService scheduler = Executors.newSingleThreadScheduledExecutor();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chat);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        getSupportActionBar().setDisplayShowHomeEnabled(true);

        // Create a hashmap that will have (position,id) as the (key,value) pairs
        final HashMap matches_map = new HashMap<>();
        // Create a list with the matches' names
        final List<String> names_list = new ArrayList<>();
        final List<String> photos_list = new ArrayList<>();

        pDialog = new ProgressDialog(this);
        pDialog.setMessage("Fetching matches ...");
        pDialog.show();

        // Create a GET request, send JSONObject.
        String tag_json_req = "get_all_matches";
        JSONObject json_params = new JSONObject();

        JsonObjectRequest jsonObjReq = new JsonObjectRequest(Request.Method.GET,
                AppConfig.URL_GET_ALL_MATCHES, json_params,
                new Response.Listener<JSONObject>() {

                    @Override
                    public void onResponse(JSONObject response) {
                        Log.d(TAG, response.toString());
                        try {
                            int count = -1;
                            try {
                                count = response.getInt("count");
                            } catch(NumberFormatException nfe) {
                                System.out.println("Could not parse " + nfe);
                            }
                            if (count <= 0){
                                Log.d(TAG, "El usuario no tiene matches");
                                pDialog.hide();
                                pDialog.dismiss();
                                return;
                            }
                            JSONArray matches = response.getJSONArray("matches");
                            for (int i = 0; i < matches.length(); i++){
                                JSONObject user = matches.getJSONObject(i).getJSONObject("user");
                                String id = user.getString("id");
                                String name = user.getString("name");
                                String photo = user.getString("photo_profile");
                                // Store data into local containers
                                matches_map.put(i,id);
                                names_list.add(i,name);
                                photos_list.add(i,photo);
                                pDialog.hide();
                                pDialog.dismiss();
                            }
                            construct(names_list,photos_list,matches_map);
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                    }
                }, new Response.ErrorListener() {

            @Override
            public void onErrorResponse(VolleyError error) {
                VolleyLog.d(TAG, "Error: " + error.getMessage());
                Log.d(TAG, error.toString());
                pDialog.hide();
                pDialog.dismiss();
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

    public void construct(List<String> names_list, List<String> photos_list, final HashMap matches_map){
        // Create a custom list adapter to populate the list of matches.
        String[] names_array = names_list.toArray(new String[names_list.size()]);
        String[] photos_array = photos_list.toArray(new String[photos_list.size()]);
        CustomListAdapter adapter = new CustomListAdapter(this,names_array,photos_array);
        ListView listView = (ListView) findViewById(R.id.chat_list);
        listView.setAdapter(adapter);

        // Set the click listener to start a conversation when a match is clicked.
        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view,
                                    int position, long id) {
                String match_id = (String) matches_map.get(position);
                Intent intent = new Intent(ChatActivity.this, MessageActvity.class);
                intent.putExtra("Match ID",match_id);
                Log.d("CHAT to MESSAGE",match_id);
                startActivity(intent);
            }
        });
    }

    @Override
    protected void onStart() {
        super.onStart();

        scheduler.scheduleAtFixedRate
                (new Runnable() {
                    public void run() {
                        Log.i(TAG,"Getting messages");
                        getMessages();
                    }
                }, 0, 10, TimeUnit.SECONDS);
    }

    @Override
    protected void onStop() {
        super.onStop();
        scheduler.shutdown();
        while (!scheduler.isTerminated());
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
                            JSONArray messages = response.getJSONArray("messages");
                            for (int i = 0; i < messages.length(); i++){
                                JSONObject message = messages.getJSONObject(i).getJSONObject("message");
                                String from_id = message.getString("from");
                                String text = message.getString("message");
                                Log.d(TAG,from_id+" "+text);
                                Message msg = new Message(from_id,text,false);
                                saveMessage(msg);
                            }
                        } catch (JSONException e) {
                            //e.printStackTrace();
                            Log.d(TAG, "El usuario no tiene mensajes nuevos");
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

    private void saveMessage(Message message){
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
        try {
            OutputStream fo = new FileOutputStream(file, true);
            fo.write(data.getBytes());
            fo.close();
            Log.e(TAG,"Message saved for conversation with id: "+id);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
