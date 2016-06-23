package com.taller2.matcherapp;

import android.content.Intent;
import android.os.Bundle;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.os.Handler;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;

import com.android.volley.AuthFailureError;
import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.VolleyLog;
import com.android.volley.toolbox.JsonObjectRequest;
import com.taller2.matcherapp.app.AppConfig;
import com.taller2.matcherapp.app.AppController;
import com.taller2.matcherapp.helper.myMessage;
import com.taller2.matcherapp.helper.MessagesListAdapter;
import com.taller2.matcherapp.helper.SQLiteHandler;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

public class MessageActvity extends AppCompatActivity {

    private static final String TAG = MessageActvity.class.getSimpleName();
    private static final int DO_LOAD = 1;
    private String match_id;
    private Button btnSend;
    private ArrayList listMessages;
    private EditText textField;
    private MessagesListAdapter adapter;
    private SQLiteHandler db;
    ScheduledExecutorService scheduler = Executors.newSingleThreadScheduledExecutor();
    Handler h;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_message);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        getSupportActionBar().setDisplayShowHomeEnabled(true);

        db = new SQLiteHandler(getApplicationContext());
        final HashMap<String, String> user = db.getUserDetails();

        Intent intent = getIntent();
        match_id = intent.getStringExtra("Match ID");
        textField = (EditText) findViewById(R.id.messageEdit);

        listMessages = new ArrayList<>();
        adapter = new MessagesListAdapter(this, listMessages);
        final ListView listViewMessages = (ListView) findViewById(R.id.messagesContainer);
        listViewMessages.setAdapter(adapter);
        listViewMessages.setSelection(adapter.getCount()-1);

        cargarMensajes();

        h = new Handler(){
            @Override
            public void handleMessage(Message msg){
                if(msg.what == DO_LOAD){
                    cargarMensajes();
                }else{
                    Log.e(TAG,"Error thread");
                }
            }
        };

        btnSend = (Button)findViewById(R.id.chatSendButton);
        // Register the onClick listener with the implementation above
        btnSend.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v)
            {
                String text = textField.getText().toString();
                myMessage msg = new myMessage(match_id,text,true);
                listMessages.add(msg);
                saveMessage(msg);
                sendMessage(msg);
                adapter.notifyDataSetChanged();
                textField.setText("");
            }
        });
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_message, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.action_profile:
                Intent profile_intent = new Intent(MessageActvity.this, MatchActivity.class);
                profile_intent.putExtra("Match ID",match_id);
                startActivity(profile_intent);
                return true;

            default:
                // If we got here, the user's action was not recognized.
                // Invoke the superclass to handle it.
                return super.onOptionsItemSelected(item);
        }
    }

    @Override
    protected void onStart() {
        super.onStart();

        scheduler.scheduleAtFixedRate
                (new Runnable() {
                    public void run() {
                        Log.i(TAG,"Getting messages");
                        getMessages();
                        h.sendEmptyMessage(DO_LOAD);
                    }
                }, 0, 10, TimeUnit.SECONDS);
    }

    @Override
    protected void onStop() {
        super.onStop();
        scheduler.shutdown();
        while (!scheduler.isTerminated());
    }

    public void parseContents(String contents){
        String lines[] = contents.split("\\r?\\n");
        for (int i = 0; i < lines.length; i++){
            int iend = lines[i].indexOf(","); //this finds the first occurrence of ","
            if (iend != -1) {
                String isSelf= lines[i].substring(0 , iend);
                String text = lines[i].substring(iend+1, lines[i].length());
                myMessage msg = new myMessage("idk",text, Boolean.valueOf(isSelf));
                listMessages.add(msg);
            }
        }
    }

    public void cargarMensajes(){
        String filePath = "data/data/com.taller2.matcherapp/"+match_id+".txt";
        File file = new File(filePath);
        if (file.exists()){
            int length = (int) file.length();
            byte[] bytes = new byte[length];
            try {
                FileInputStream fis = new FileInputStream(file);
                fis.read(bytes);
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
            String contents = new String(bytes);
            Log.d(TAG,contents);
            parseContents(contents);
        }
        else {
            try {
                file.createNewFile();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public void saveMessage(myMessage myMessage){

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
            Log.e("Save myMessage","myMessage saved for conversation with id: "+id);
        } catch (IOException e) {
            e.printStackTrace();
        }
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
                                myMessage msg = new myMessage(from_id,text,false);
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

    public void sendMessage(myMessage msg){
        // Create a POST request, send JSONObject.
        String tag_json_req = "send_message";
        JSONObject json_params = new JSONObject();
        try {
            // Pongo el id de a quien se lo mando.
            json_params.put("id",match_id);
            json_params.put("message",msg.getMessage());
        } catch (JSONException e) {
            e.printStackTrace();
        }


        JsonObjectRequest jsonObjReq = new JsonObjectRequest(Request.Method.POST,
                AppConfig.URL_SEND_MESSAGE, json_params,
                new Response.Listener<JSONObject>() {

                    @Override
                    public void onResponse(JSONObject response) {
                        Log.d(TAG, response.toString());
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
}
