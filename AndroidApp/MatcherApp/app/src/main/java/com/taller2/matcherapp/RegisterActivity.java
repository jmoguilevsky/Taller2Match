package com.taller2.matcherapp;

import android.app.ProgressDialog;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioButton;
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

public class RegisterActivity extends AppCompatActivity {

    private static final String TAG = RegisterActivity.class.getSimpleName();
    private Button btnRegister;
    private Button btnLinkToLogin;
    private EditText inputFullName;
    private EditText inputEmail;
    private EditText inputAlias;
    private EditText inputPassword;
    private ProgressDialog pDialog;
    private SessionManager session;
    private String sex_interest = "";
    private String user_gender = "";
    private SQLiteHandler db;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_register);

        inputFullName = (EditText) findViewById(R.id.name);
        inputEmail = (EditText) findViewById(R.id.email);
        inputPassword = (EditText) findViewById(R.id.password);
        inputAlias= (EditText) findViewById(R.id.alias);
        btnRegister = (Button) findViewById(R.id.btnRegister);
        btnLinkToLogin = (Button) findViewById(R.id.btnLinkToLoginScreen);

        // Progress dialog
        pDialog = new ProgressDialog(this);
        pDialog.setCancelable(false);

        // Session manager
        session = new SessionManager(getApplicationContext());

        // SQLite database handler
        db = new SQLiteHandler(getApplicationContext());

        // Check if user is already logged in or not
        if (session.isLoggedIn()) {
            // User is already logged in. Take him to main activity
            Intent intent = new Intent(RegisterActivity.this,
                    MainActivity.class);
            startActivity(intent);
            finish();
        }

        // Register Button Click event
        btnRegister.setOnClickListener(new View.OnClickListener() {
            public void onClick(View view) {
                String name = inputFullName.getText().toString().trim();
                String email = inputEmail.getText().toString().trim();
                String password = inputPassword.getText().toString().trim();
                String alias = inputAlias.getText().toString().trim();

                sex_interest.trim();
                user_gender.trim();

                if (!name.isEmpty() && !email.isEmpty() && !password.isEmpty() &&
                        !sex_interest.isEmpty() && !user_gender.isEmpty() && !alias.isEmpty()) {
                    registerUser(name, alias, user_gender, email, password, sex_interest);
                } else {
                    Toast.makeText(getApplicationContext(),
                            "Please enter your details!", Toast.LENGTH_LONG).show();
                }
            }
        });

        // Link to Login Screen
        btnLinkToLogin.setOnClickListener(new View.OnClickListener() {

            public void onClick(View view) {
                Intent i = new Intent(getApplicationContext(),
                        LoginActivity.class);
                startActivity(i);
                finish();
            }
        });

    }

    public void onRadioButtonClickedGender(View view) {
        // Is the button now checked?
        boolean checked = ((RadioButton) view).isChecked();

        // Check which radio button was clicked
        switch(view.getId()) {
            case R.id.btn_male:
                if (checked)
                    user_gender = "Male";
                break;
            case R.id.btn_female:
                if (checked)
                    user_gender = "Female";
                break;
        }
    }

    public void onRadioButtonClickedSexInterest(View view) {
        // Is the button now checked?
        boolean checked = ((RadioButton) view).isChecked();

        // Check which radio button was clicked
        switch(view.getId()) {
            case R.id.btn_men:
                if (checked)
                    sex_interest = "Male";
                break;
            case R.id.btn_women:
                if (checked)
                    sex_interest = "Female";
                break;
        }
    }

    // Function that creates POST request to register user with the parameters provided.
    // If registration is successful, user is taken to Login activity,
    private void registerUser(final String name, final String alias, final String user_gender, final String email,
                              final String password, final String sex_interest) {
        // Tag used to cancel the request
        String tag_json_req = "req_register";

        pDialog.setMessage("Registering ...");
        showDialog();

        // We create the JSONObject defined in the API (check documentation) to be POSTed to the server
        JSONObject json_params = new JSONObject();
        try{
            JSONObject json_info = new JSONObject();
            json_info.put("password",password);
            json_info.put("email",email);

            JSONObject location = new JSONObject();
            location.put("latitude", -121.34343);
            location.put("longitude", 45.51119);

            JSONObject json_sex_interest = new JSONObject();
            json_sex_interest.put("category","sex");
            json_sex_interest.put("value",sex_interest);

            JSONArray json_array_interests = new JSONArray();
            json_array_interests.put(json_sex_interest);

            JSONObject json_user = new JSONObject();
            json_user.put("name",name);
            json_user.put("alias",alias);
            json_user.put("email",email);
            json_user.put("sex",user_gender);
            // TODO agregar campo edad
            json_user.put("interests",json_array_interests);
            json_user.put("location",location);

            json_params.put("info",json_info);
            json_params.put("user",json_user);

            Log.d(TAG,json_params.toString());
        } catch (JSONException e) {
            e.printStackTrace();
        }

        // Create the request for a JSONObject
        JsonObjectRequest jsonObjReq = new JsonObjectRequest(Request.Method.POST,
                AppConfig.URL_REGISTER, json_params,
                new Response.Listener<JSONObject>() {

                    @Override
                    public void onResponse(JSONObject response) {
                        Log.d(TAG, response.toString());
                        Toast.makeText(getApplicationContext(),
                                "Registration successful!", Toast.LENGTH_LONG).show();
                        // Call the login activity.
                        Intent intent = new Intent(RegisterActivity.this, LoginActivity.class);
                        startActivity(intent);
                        finish();
                        hideDialog();
                    }
                }, new Response.ErrorListener() {

            @Override
            public void onErrorResponse(VolleyError error) {
                VolleyLog.d(TAG, "Error: " + error.getMessage());
                Log.d(TAG, error.toString());
                hideDialog();
            }

        });

        // Adding request to request queue
        AppController.getInstance().addToRequestQueue(jsonObjReq, tag_json_req);
        hideDialog();
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
