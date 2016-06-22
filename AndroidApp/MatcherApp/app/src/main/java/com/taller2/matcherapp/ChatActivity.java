package com.taller2.matcherapp;

import android.app.ProgressDialog;
import android.content.Intent;
import android.os.Bundle;
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
import com.taller2.matcherapp.helper.CustomListAdapter;
import com.taller2.matcherapp.helper.SQLiteHandler;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ChatActivity extends AppCompatActivity {

    private final static String TAG = ChatActivity.class.getSimpleName();
    private ProgressDialog pDialog;


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
                                count = Integer.parseInt(response.getString("count"));
                            } catch(NumberFormatException nfe) {
                                System.out.println("Could not parse " + nfe);
                            }
                            if (count <= 0){
                                Log.d(TAG, "El usuario no tiene matches");
                                return;
                            }
                            JSONArray matches = response.getJSONArray("matches");
                            for (int i = 0; i < matches.length(); i++){
                                JSONObject user = matches.getJSONObject(i).getJSONObject("user");
                                String id = user.getString("id");
                                String name = user.getString("name");
                                String photo = user.getString("photo");
                                // Store data into local containers
                                matches_map.put(i,id);
                                names_list.add(i,name);
                                photos_list.add(i,photo);
                                pDialog.hide();
                                pDialog.dismiss();
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
}
