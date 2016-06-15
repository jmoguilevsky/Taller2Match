package com.taller2.matcherapp;

import android.app.ProgressDialog;
import android.content.Intent;
import android.graphics.Bitmap;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.android.volley.AuthFailureError;
import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.VolleyLog;
import com.android.volley.toolbox.JsonObjectRequest;
import com.taller2.matcherapp.app.AppConfig;
import com.taller2.matcherapp.app.AppController;
import com.taller2.matcherapp.helper.SQLiteHandler;
import com.taller2.matcherapp.helper.SessionManager;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.HashMap;
import java.util.Map;

public class MainActivity extends AppCompatActivity {

    private TextView txtEmail;
    private ImageView imgMatch;
    private Button btnFind;
    private ImageView iconHeart;
    private ImageView iconCross;
    private int LIKE_MATCH = 1;
    private int DISLIKE_MATCH = 2;
    private static final String TAG = MainActivity.class.getSimpleName();
    private String id_candidate;

    private SQLiteHandler db;
    private SessionManager session;
    private ProgressDialog pDialog;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar myToolbar = (Toolbar) findViewById(R.id.my_toolbar);
        setSupportActionBar(myToolbar);

        // Obtain and assign views
        txtEmail = (TextView) findViewById(R.id.email);
        imgMatch = (ImageView) findViewById(R.id.match_image);
        //btnFind = (Button) findViewById(R.id.btnFind);
        iconHeart = (ImageView) findViewById(R.id.match_accept);
        iconCross = (ImageView) findViewById(R.id.match_reject);

        // session manager
        session = new SessionManager(getApplicationContext());
        if (!session.isLoggedIn()) {
            logoutUser();
        }

        // SqLite database handler
        db = new SQLiteHandler(getApplicationContext());
        // Fetching user details from sqlite
        HashMap<String, String> user = db.getUserDetails();
        // Get user details from the database
        String email = user.get("email");
        // Displaying the user details on the screen
        txtEmail.setText(email);

        // Match piture image click event
        View.OnClickListener match_clickListener = new View.OnClickListener() {
            public void onClick(View v) {
                if (v.equals(imgMatch)) {
                    // Define what to do when user clicks image
                }
                else if (v.equals(iconHeart)){
                    // Accept (heart) button click event
                    acceptMatch();
                }
                else if (v.equals(iconCross)) {
                    // Reject (cross) match button click event
                    rejectMatch();
                }
                else if (v.equals(btnFind)) {
                    // Find match button click event
                    findMatch();
                }
            }
        };
        // Assign listener to all icons and buttons
        imgMatch.setOnClickListener(match_clickListener);
        iconHeart.setOnClickListener(match_clickListener);
        iconCross.setOnClickListener(match_clickListener);
        //btnFind.setOnClickListener(match_clickListener);

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.activity_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.action_settings:
                // User chose the "Settings" item, show the app settings UI...
                return true;

            case R.id.action_chat:
                Intent intent = new Intent(MainActivity.this, ChatActivity.class);
                startActivity(intent);
                return true;

            case R.id.action_profile:
                Intent profile_intent = new Intent(MainActivity.this, ProfileActivity.class);
                startActivity(profile_intent);
                return true;

            case R.id.action_logout:
                logoutUser();
                return true;

            default:
                // If we got here, the user's action was not recognized.
                // Invoke the superclass to handle it.
                return super.onOptionsItemSelected(item);
        }
    }

    /**
     * Logging out the user. Will set isLoggedIn flag to false in shared
     * preferences Clears the user data from sqlite users table
     * */
    private void logoutUser() {
        session.setLogin(false);

        final HashMap<String, String> user = db.getUserDetails();
        final String token = user.get("token");
        Log.d("token",token);

        // Create a POST request, send JSONObject.
        // On success expect an empty JSON
        // On failute expect a JSON with an error field
        String tag_json_req = "req_logout";
        JSONObject json_params = new JSONObject();

        JsonObjectRequest jsonObjReq = new JsonObjectRequest(Request.Method.POST,
                AppConfig.URL_LOGOUT, json_params,
                new Response.Listener<JSONObject>() {

                    @Override
                    public void onResponse(JSONObject response) {
                        Log.d(TAG, response.toString());
                        db.deleteUsers();
                        // Launching the login activity
                        Intent intent = new Intent(MainActivity.this, LoginActivity.class);
                        startActivity(intent);
                        finish();
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
                Map<String, String> params = new HashMap<String, String>();
                params.put("Authorization", token);
                return params;
            }
        };

        // Adding request to request queue
        AppController.getInstance().addToRequestQueue(jsonObjReq, tag_json_req);
    }

    private void findMatch(){
        //imgMatch.setImageResource(R.drawable.sans);
        //imgMatch.setVisibility(View.VISIBLE);
        final HashMap<String, String> user = db.getUserDetails();
        String token = user.get("token");

        // Progress dialog
        pDialog = new ProgressDialog(this);
        pDialog.setCancelable(false);
        pDialog.setMessage("Finding Match...");
        pDialog.show();

        // Create a POST request, send JSONObject.
        // On success expect an empty JSON
        // On failute expect a JSON with an error field
        String tag_json_req = "req_candidate";
        JSONObject json_params = new JSONObject();

        JsonObjectRequest jsonObjReq = new JsonObjectRequest(Request.Method.GET,
                AppConfig.URL_FIND_CANDIDATE, json_params,
                new Response.Listener<JSONObject>() {

                    @Override
                    public void onResponse(JSONObject response) {
                        Log.d(TAG, response.toString());
                        try {
                            // We get the candidate id.
                            String cand_id = response.getString("id");
                            // We store the id to then send it to the server with the reaction to the candidate.
                            id_candidate = cand_id;
                            String cand_name = response.getString("name");
                            String cand_alias = response.getString("alias");
                            String cand_email = response.getString("email");
                            String cand_photo = response.getString("phto_profile");
                            Bitmap photo_map = AppController.getInstance().getBitmapImage(cand_photo);
                            imgMatch.setImageBitmap(photo_map);
                            JSONArray arr_interests = response.getJSONArray("interests");
                            String cand_interests = arr_interests.toString();
                            JSONObject cand_location = response.getJSONObject("location");
                            String cand_latitude = response.getString("latitude");
                            String cand_longitude = response.getString("longitude");
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                        pDialog.hide();
                    }
                }, new Response.ErrorListener() {

            @Override
            public void onErrorResponse(VolleyError error) {
                VolleyLog.d(TAG, "Error: " + error.getMessage());
                Log.d(TAG, error.toString());
                pDialog.hide();
            }

        }){
            @Override
            public Map<String, String> getHeaders() throws AuthFailureError {
                Map<String, String> params = new HashMap<String, String>();
                params.put("Authorization", user.get("token"));
                return params;
            }
        };

        // Adding request to request queue
        AppController.getInstance().addToRequestQueue(jsonObjReq, tag_json_req);

    }

    private void acceptMatch(){
        react_to_match(LIKE_MATCH);
    }

    private void rejectMatch(){
        react_to_match(DISLIKE_MATCH);
    }

    private void react_to_match(int reaction){
        String reaction_string;
        if (reaction == LIKE_MATCH){
            reaction_string = "like";
        }
        else if (reaction == DISLIKE_MATCH){
            reaction_string = "dislike";
        }
        else {
            reaction_string = "error";
        }

        // Send PUT request to server
        final HashMap<String, String> user = db.getUserDetails();
        String token = user.get("token");

        // Progress dialog
        pDialog = new ProgressDialog(this);
        pDialog.setCancelable(false);
        pDialog.setMessage("Reacting to Match...");
        pDialog.show();

        // Create a POST request, send JSONObject.
        // On success expect an empty JSON
        // On failute expect a JSON with an error field
        String tag_json_req = "req_candidate";
        JSONObject json_params = new JSONObject();
        try {
            json_params.put("id",id_candidate);
            json_params.put("reaction",reaction);
        } catch (JSONException e) {
            e.printStackTrace();
        }

        JsonObjectRequest jsonObjReq = new JsonObjectRequest(Request.Method.PUT,
                AppConfig.URL_REACT_CANDIDATE, json_params,
                new Response.Listener<JSONObject>() {

                    @Override
                    public void onResponse(JSONObject response) {
                        Log.d(TAG, response.toString());
                        pDialog.hide();
                    }
                }, new Response.ErrorListener() {

            @Override
            public void onErrorResponse(VolleyError error) {
                VolleyLog.d(TAG, "Error: " + error.getMessage());
                Log.d(TAG, error.toString());
                pDialog.hide();
            }

        }){
            @Override
            public Map<String, String> getHeaders() throws AuthFailureError {
                Map<String, String> params = new HashMap<String, String>();
                params.put("Authorization", user.get("token"));
                return params;
            }
        };

        // Adding request to request queue
        AppController.getInstance().addToRequestQueue(jsonObjReq, tag_json_req);
    }
}
