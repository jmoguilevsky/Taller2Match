package com.taller2.matcherapp;

import android.app.ProgressDialog;
import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.location.Location;
import android.support.v4.app.ActivityCompat;
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
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.GooglePlayServicesUtil;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.location.LocationRequest;
import com.google.android.gms.location.LocationServices;
import com.taller2.matcherapp.app.AppConfig;
import com.taller2.matcherapp.app.AppController;
import com.taller2.matcherapp.helper.SessionManager;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.List;

public class RegisterActivity extends AppCompatActivity implements GoogleApiClient.ConnectionCallbacks,
        GoogleApiClient.OnConnectionFailedListener {

    private static final String TAG = RegisterActivity.class.getSimpleName();
    private static final int MY_PERMISSIONS_REQUEST_FINE_LOCATION = 1;
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
    private GoogleApiClient mGoogleApiClient;
    private Location mLastLocation;
    // boolean flag to toggle periodic location updates
    private boolean mRequestingLocationUpdates = false;
    private final static int PLAY_SERVICES_RESOLUTION_REQUEST = 1000;
    private LocationRequest mLocationRequest;
    // Location updates intervals in sec
    private static int UPDATE_INTERVAL = 10000; // 10 sec
    private static int FATEST_INTERVAL = 5000; // 5 sec
    private static int DISPLACEMENT = 10; // 10 meters

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

        // First we need to check availability of play services
        if (checkPlayServices()) {
            // Building the GoogleApi client
            buildGoogleApiClient();
        }

        ActivityCompat.requestPermissions(this,
                new String[]{Manifest.permission.ACCESS_FINE_LOCATION},
                MY_PERMISSIONS_REQUEST_FINE_LOCATION);

        // Register Button Click event
        btnRegister.setOnClickListener(new View.OnClickListener() {
            public void onClick(View view) {
                String name = inputFullName.getText().toString().trim();
                String email = inputEmail.getText().toString().trim();
                String password = inputPassword.getText().toString().trim();
                String alias = inputAlias.getText().toString().trim();
                String sex = sex_interest.trim();
                String gender = user_gender.trim();
                String age = spinner_age.getSelectedItem().toString();
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

    /**
     * Creating google api client object
     * */
    protected synchronized void buildGoogleApiClient() {
        mGoogleApiClient = new GoogleApiClient.Builder(this)
                .addConnectionCallbacks(this)
                .addOnConnectionFailedListener(this)
                .addApi(LocationServices.API).build();
    }

    /**
     * Method to verify google play services on the device
     * */
    private boolean checkPlayServices() {
        int resultCode = GooglePlayServicesUtil
                .isGooglePlayServicesAvailable(this);
        if (resultCode != ConnectionResult.SUCCESS) {
            if (GooglePlayServicesUtil.isUserRecoverableError(resultCode)) {
                GooglePlayServicesUtil.getErrorDialog(resultCode, this,
                        PLAY_SERVICES_RESOLUTION_REQUEST).show();
            } else {
                Toast.makeText(getApplicationContext(),
                        "This device is not supported.", Toast.LENGTH_LONG)
                        .show();
                finish();
            }
            return false;
        }
        return true;
    }

    @Override
    protected void onStart() {
        super.onStart();
        if (mGoogleApiClient != null) {
            mGoogleApiClient.connect();
        }
    }

    @Override
    protected void onResume() {
        super.onResume();

        checkPlayServices();
    }

    /**
     * Google api callback methods
     */
    @Override
    public void onConnectionFailed(ConnectionResult result) {
        Log.i(TAG, "Connection failed: ConnectionResult.getErrorCode() = "
                + result.getErrorCode());
    }

    @Override
    public void onConnected(Bundle arg0) {
    }

    @Override
    public void onConnectionSuspended(int arg0) {
        mGoogleApiClient.connect();
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

            if (ActivityCompat.checkSelfPermission(this, android.Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED && ActivityCompat.checkSelfPermission(this, android.Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
                // TODO: Consider calling
                //    ActivityCompat#requestPermissions
                // here to request the missing permissions, and then overriding
                //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
                //                                          int[] grantResults)
                // to handle the case where the user grants the permission. See the documentation
                // for ActivityCompat#requestPermissions for more details.
                return;
            }
            mLastLocation = LocationServices.FusedLocationApi.getLastLocation(mGoogleApiClient);

            double latitude = -121.34343;
            double longitude = 45.51119;

            if (mLastLocation != null) {
                latitude = mLastLocation.getLatitude();
                longitude = mLastLocation.getLongitude();
            } else {
                Toast.makeText(getApplicationContext(),"(Couldn't get the location. Make sure location is enabled on the device)",Toast.LENGTH_LONG).show();
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
