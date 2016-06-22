package com.taller2.matcherapp;

import android.app.ProgressDialog;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

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

public class LoginActivity extends AppCompatActivity {

    private static final String TAG = LoginActivity.class.getSimpleName();
    private Button btnLogin;
    private Button btnLinkToRegister;
    private EditText inputEmail;
    private EditText inputPassword;
    private ProgressDialog pDialog;
    private SessionManager session;
    private SQLiteHandler db;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        inputEmail = (EditText) findViewById(R.id.email);
        inputPassword = (EditText) findViewById(R.id.password);
        btnLogin = (Button) findViewById(R.id.btnLogin);
        btnLinkToRegister = (Button) findViewById(R.id.btnLinkToRegisterScreen);

        // Progress dialog
        pDialog = new ProgressDialog(this);
        pDialog.setCancelable(false);

        // SQLite database handler
        db = new SQLiteHandler(getApplicationContext());

        // Session manager
        session = new SessionManager(getApplicationContext());

        // Check if user is already logged in or not
        if (session.isLoggedIn()) {
            // User is already logged in. Take him to main activity
            Intent intent = new Intent(LoginActivity.this, MainActivity.class);
            startActivity(intent);
            finish();
        }

        // Login button Click Event
        btnLogin.setOnClickListener(new View.OnClickListener() {

            public void onClick(View view) {
                String email = inputEmail.getText().toString().trim();
                String password = inputPassword.getText().toString().trim();

                // Check for empty data in the form
                if (!email.isEmpty() && !password.isEmpty()) {
                    // login user
                    checkLogin(email, password);
                } else {
                    // Prompt user to enter credentials
                    Toast.makeText(getApplicationContext(),
                            "Please enter the credentials!", Toast.LENGTH_LONG)
                            .show();
                }
            }

        });

        // Link to Register Screen
        btnLinkToRegister.setOnClickListener(new View.OnClickListener() {

            public void onClick(View view) {
                Intent i = new Intent(getApplicationContext(),
                        RegisterActivity.class);
                startActivity(i);
                finish();
            }
        });

    }

    // Function to verify login details at the database specified in the login url.
    // If login is successful, the session Login is set to true and user is taken to main activity.
    private void checkLogin(final String email, final String password) {
        // Tag used to cancel the request
        String tag_json_req = "req_login";

        pDialog.setMessage("Logging in ...");
        showDialog();

        // Post params to be sent to the server
        HashMap<String, String> params = new HashMap<>();
        params.put("email", email);
        params.put("password", password);
        JSONObject json_params = new JSONObject(params);
        Log.d("DEBUG",json_params.toString());

        // Create login session
        session.setLogin(true);

        // Add user to database
        String name_stud = "Seba Elizalde";
        String alias_stud = "SE";
        String gender_stud = "male";
        String email_stud = "seba@gmail.com";
        // Set up interests stud
        JSONObject json_sex_interest = new JSONObject();
        JSONObject json_band_interest = new JSONObject();
        JSONObject json_led_interest = new JSONObject();
        JSONArray json_array_interests = new JSONArray();
        try {
            json_sex_interest.put("category","sex");
            json_sex_interest.put("value","female");

            json_band_interest.put("category","music/band");
            json_band_interest.put("value","Deep Purple");

            json_led_interest.put("category","music/band");
            json_led_interest.put("value","Led Zeppelin");

            json_array_interests.put(json_sex_interest);
            json_array_interests.put(json_band_interest);
            json_array_interests.put(json_led_interest);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        String interests_stud = json_array_interests.toString();
        // Set up photo stud
        Bitmap profile_photo_map = BitmapFactory.decodeResource(getApplicationContext().getResources(),R.drawable.blank_profile_picture);
        String profile_photo_stud = AppController.getInstance().getStringImage(profile_photo_map);
        // Set up location stud
        JSONObject json_location = new JSONObject();
        try {
            json_location.put("latitude",-121.34343);
            json_location.put("longitude",45.51119);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        String location_stud = json_location.toString();
        String token_stud = "123token123";
        db.addUser(name_stud, alias_stud, gender_stud, email_stud, interests_stud,
                profile_photo_stud, location_stud, token_stud);
        hideDialog();
        Intent intent = new Intent(LoginActivity.this,
                MainActivity.class);
        startActivity(intent);
        finish();

        // Create the request for a JSONObject
        /*final JsonObjectRequest jsonObjReq = new JsonObjectRequest(Request.Method.POST,
                AppConfig.URL_LOGIN, new JSONObject(params),
                new Response.Listener<JSONObject>() {

                    @Override
                    public void onResponse(JSONObject response) {
                        Log.d(TAG, response.toString());
                        try {
                            // user successfully logged in
                            // Create login session
                            session.setLogin(true);

                            // Add user and his data to SQLite local database.
                            String token = response.getString("token");
                            JSONObject user = new JSONObject(response.getString("user"));
                            String name = user.getString("name");
                            String alias = user.getString("alias");
                            String user_gender = user.getString("sex");
                            JSONArray interests = user.getJSONArray("interests");
                            String user_interests = interests.toString();
                            Log.d("Interests",user_interests);

                            //Bitmap profile_photo_map = BitmapFactory.decodeResource(getApplicationContext().getResources(),R.drawable.blank_profile_picture);
                            //String profile_photo_stud = AppController.getInstance().getStringImage(profile_photo_map);
                            String profile_photo = user.getString("photo_profile");
                            JSONObject location = user.getJSONObject("location");
                            String user_location = location.toString();

                            db.addUser(name,alias,user_gender,email,user_interests,profile_photo,user_location,token);
                            hideDialog();
                            Intent intent = new Intent(LoginActivity.this,
                                    MainActivity.class);
                            startActivity(intent);
                            finish();
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                        hideDialog();
                    }
                }, new Response.ErrorListener() {

            @Override
            public void onErrorResponse(VolleyError error) {
                VolleyLog.d(TAG, "Error: " + error.getMessage());
                Log.e(TAG, "Login Error: " + error.getMessage());
                Toast.makeText(getApplicationContext(),
                        "Server Error " + error.getMessage() + ". Please try again.", Toast.LENGTH_LONG).show();
                hideDialog();
            }
        });

        // Adding request to request queue
        AppController.getInstance().addToRequestQueue(jsonObjReq, tag_json_req);*/
    }

    private void showDialog() {
        if (!pDialog.isShowing())
            pDialog.show();
    }

    private void hideDialog() {
        if (pDialog.isShowing())
            pDialog.dismiss();
    }
}
