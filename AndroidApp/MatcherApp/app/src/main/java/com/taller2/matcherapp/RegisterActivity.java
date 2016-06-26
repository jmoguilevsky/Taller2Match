package com.taller2.matcherapp;

import android.app.ProgressDialog;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.SeekBar;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;


import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.VolleyLog;
import com.android.volley.toolbox.JsonObjectRequest;
import com.taller2.matcherapp.app.AppController;
import com.taller2.matcherapp.helper.GPSTracker;
import com.taller2.matcherapp.helper.SessionManager;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.List;

public class RegisterActivity extends AppCompatActivity{

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
    private TextView inputDistance;
    private Spinner spinner_age;
    private GPSTracker gps;


    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_register);

        inputFullName = (EditText) findViewById(R.id.name);
        inputEmail = (EditText) findViewById(R.id.email);
        inputPassword = (EditText) findViewById(R.id.password);
        inputAlias = (EditText) findViewById(R.id.alias);
        btnRegister = (Button) findViewById(R.id.btnRegister);
        btnLinkToLogin = (Button) findViewById(R.id.btnLinkToLoginScreen);
        inputDistance = (TextView) findViewById(R.id.display_distance);
        spinner_age = (Spinner) findViewById(R.id.spinner_age);

        // Progress dialog
        pDialog = new ProgressDialog(this);
        pDialog.setCancelable(false);

        // Session manager
        session = new SessionManager(getApplicationContext());

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
                String sex = sex_interest.trim();
                String gender = user_gender.trim();
                String age = spinner_age.getSelectedItem().toString().trim();
                String distance = inputDistance.getText().toString().replaceAll("[^0-9?!\\.]", ""); // get only the number

                if (!isEmailValid(email)) {
                    Toast.makeText(getApplicationContext(),
                            "Please enter a valid email!", Toast.LENGTH_LONG).show();
                } else if (!name.isEmpty() && !email.isEmpty() && !password.isEmpty() &&
                        !sex.isEmpty() && !gender.isEmpty() && !alias.isEmpty()) {
                    registerUser(name, alias, gender, email, password, sex, distance, age);
                } else {
                    Toast.makeText(getApplicationContext(),
                            "Please enter ALL of your details!", Toast.LENGTH_LONG).show();
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

        List age = new ArrayList<>();
        for (int i = 18; i <= 80; i++) {
            age.add(Integer.toString(i));
        }
        ArrayAdapter<Integer> spinnerArrayAdapter = new ArrayAdapter<>(this, android.R.layout.simple_spinner_item, age);
        spinnerArrayAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner_age.setAdapter(spinnerArrayAdapter);

        // Seekbar set up
        SeekBar mSeekbar = (SeekBar) findViewById(R.id.age_seekbar);

        mSeekbar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                inputDistance.setText(String.valueOf(progress + 1) + " km"); // to set the minimum at 1
            }

            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            public void onStopTrackingTouch(SeekBar seekBar) {
            }
        });

    }

    boolean isEmailValid(CharSequence email) {
        return android.util.Patterns.EMAIL_ADDRESS.matcher(email).matches();
    }

    public void onRadioButtonClickedGender(View view) {
        // Is the button now checked?
        boolean checked = ((RadioButton) view).isChecked();

        // Check which radio button was clicked
        switch (view.getId()) {
            case R.id.btn_male:
                if (checked)
                    user_gender = "male";
                break;
            case R.id.btn_female:
                if (checked)
                    user_gender = "female";
                break;
        }
    }

    public void onRadioButtonClickedSexInterest(View view) {
        // Is the button now checked?
        boolean checked = ((RadioButton) view).isChecked();

        // Check which radio button was clicked
        switch (view.getId()) {
            case R.id.btn_men:
                if (checked)
                    // User wants to meet men
                    sex_interest = "male";
                break;
            case R.id.btn_women:
                if (checked)
                    // User wants to
                    sex_interest = "female";
                break;
        }
    }

    // Function that creates POST request to register user with the parameters provided.
    // If registration is successful, user is taken to Login activity,
    private void registerUser(final String name, final String alias, final String user_gender, final String email,
                              final String password, final String sex_interest, final String distance, final String user_age) {
        // Tag used to cancel the request
        String tag_json_req = "req_register";

        pDialog.setMessage("Registering ...");
        showDialog();

        // We create the JSONObject defined in the API (check documentation) to be POSTed to the server
        JSONObject json_params = new JSONObject();
        try {
            JSONObject json_info = new JSONObject();
            json_info.put("password", password);
            json_info.put("email", email);
            json_info.put("distance", distance);

            JSONObject location = new JSONObject();
            double latitude = -121.34343;
            double longitude = 45.51119;

            // create class object
            gps = new GPSTracker(RegisterActivity.this);

            // check if GPS enabled
            if(gps.canGetLocation()){

                latitude = gps.getLatitude();
                longitude = gps.getLongitude();

            }else{
                // can't get location
                // GPS or Network is not enabled
                // Ask user to enable GPS/network in settings
                gps.showSettingsAlert();
            }

            location.put("latitude", latitude);
            location.put("longitude", longitude);

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

            Bitmap map = BitmapFactory.decodeResource(getApplicationContext().getResources(),R.drawable.blank_profile_picture);
            String foto = AppController.getInstance().getStringImage(map);
            json_user.put("photo_profile",foto);

            int int_age = Integer.parseInt(user_age);
            json_user.put("age",int_age);
            json_user.put("interests",json_array_interests);
            json_user.put("location",location);

            json_params.put("info",json_info);
            json_params.put("user",json_user);

            Log.d(TAG,json_params.toString());
        } catch (JSONException e) {
            e.printStackTrace();
        }

        // Create a POST request, send JSONObject.
        // On success expect an empty JSON
        // On failute expect a JSON with an error field
        JsonObjectRequest jsonObjReq = new JsonObjectRequest(Request.Method.POST,
                AppController.getInstance().getRegister(), json_params,
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
                Toast.makeText(getApplicationContext(),"Registration failed!", Toast.LENGTH_LONG).show();
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
