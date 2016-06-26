package com.taller2.matcherapp;

import android.app.ProgressDialog;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.graphics.Typeface;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.MenuItem;
import android.widget.ImageView;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

import com.android.volley.AuthFailureError;
import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.VolleyLog;
import com.android.volley.toolbox.JsonObjectRequest;
import com.taller2.matcherapp.app.AppController;
import com.taller2.matcherapp.helper.SQLiteHandler;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.HashMap;
import java.util.Map;

public class MatchActivity extends AppCompatActivity {

    private static final String TAG = MatchActivity.class.getSimpleName();
    private ProgressDialog pDialog;
    private SQLiteHandler db;
    private TextView match_alias;
    private TextView match_email;
    private String match_id;
    private String match_name;
    private TextView match_age;
    private TextView match_distance;
    private ImageView match_picture;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_match);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        getSupportActionBar().setDisplayShowHomeEnabled(true);

        // Progress dialog
        pDialog = new ProgressDialog(this);
        pDialog.setCancelable(false);
        pDialog.setMessage("Loading match profile...");
        pDialog.show();

        // Obtain and assign the views
        match_alias = (TextView) findViewById(R.id.match_alias);
        match_email = (TextView) findViewById(R.id.match_email);
        match_age = (TextView) findViewById(R.id.match_age);
        match_distance = (TextView) findViewById(R.id.match_distance);
        match_picture = (ImageView) findViewById(R.id.match_profile_pic);
        add_row_interests_table("Category","Interest",true);

        // SqLite database handler
        db = new SQLiteHandler(getApplicationContext());
        final HashMap<String, String> user = db.getUserDetails();

        // Create a POST request, send JSONObject.
        // On success expect an empty JSON
        // On failute expect a JSON with an error field
        String tag_json_req = "req_candidate";
        JSONObject json_params = new JSONObject();
        Intent intent = getIntent();
        match_id = intent.getStringExtra("Match ID");
        match_name = intent.getStringExtra("name");
        try {
            json_params.put("id",match_id);
        } catch (JSONException e) {
            e.printStackTrace();
        }

        JsonObjectRequest jsonObjReq = new JsonObjectRequest(Request.Method.PUT,
                AppController.getInstance().getViewMatch(), json_params,
                new Response.Listener<JSONObject>() {

                    @Override
                    public void onResponse(JSONObject response) {
                        Log.d(TAG, response.toString());
                        try {
                            JSONObject user = response.getJSONObject("user");
                            // Set the title to the match's name
                            getSupportActionBar().setTitle(user.getString("name"));

                            match_alias.setText(user.getString("alias"));
                            match_email.setText(user.getString("email"));
                            // TODO match age
                            String cand_photo = user.getString("photo_profile");
                            Bitmap photo_map = AppController.getInstance().getBitmapImage(cand_photo);
                            match_picture.setImageBitmap(photo_map);
                            JSONArray arr_interests = user.getJSONArray("interests");
                            Log.d(TAG,arr_interests.toString());
                            for (int i=0; i < arr_interests.length(); i++){
                                // Add each interest to the table
                                JSONObject interest = arr_interests.getJSONObject(i);
                                String category = interest.getString("category");
                                String value = interest.getString("value");
                                add_row_interests_table(category, value,false);
                            }

                            // Get the candidate location and calculate the distance.
                            JSONObject cand_location = user.getJSONObject("location");
                            String cand_lat = cand_location.getString("latitude");
                            String cand_long = cand_location.getString("longitude");
                            //int distancia = user.getInt("distance");
                            //match_distance.setText(String.valueOf(distancia));

                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                        pDialog.hide();
                        pDialog.dismiss();
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
                Map<String, String> params = new HashMap<String, String>();
                params.put("Authorization", user.get("token"));
                return params;
            }
        };
        // Adding request to request queue
        AppController.getInstance().addToRequestQueue(jsonObjReq, tag_json_req);
    }

    // Function that adds rows with the format Category / Interest to the table.
    public void add_row_interests_table(String category, String interest, boolean isHeader){
        // The interests table is populated dynamically, so we get its layout
        TableLayout interests_layout = (TableLayout) findViewById(R.id.match_interests_table);
        // Create a new row to add to the table, set the row's layout.
        TableRow interest_row = new TableRow(this);
        interest_row.setLayoutParams(new TableRow.LayoutParams(TableRow.LayoutParams.MATCH_PARENT, TableRow.LayoutParams.WRAP_CONTENT));
        interest_row.setBackgroundColor(Color.parseColor("#ccccff"));
        interest_row.setWeightSum(2);
        // Each row will have 2 columns: Category / Interest
        // which will be TextView / TextView .Set them up:
        TextView viewCategory = new TextView(this);
        TableRow.LayoutParams lp = new TableRow.LayoutParams(0, -2 /*WRAP_CONTENT*/, 1.0f);
        viewCategory.setLayoutParams(lp);
        viewCategory.setText(category);
        viewCategory.setTextSize(20);
        if (isHeader){
            viewCategory.setTypeface(viewCategory.getTypeface(), Typeface.BOLD);
        }

        TextView viewInterest = new TextView(this);
        viewCategory.setLayoutParams(lp);
        viewInterest.setText(interest);
        viewInterest.setTextSize(20);
        if (isHeader){
            viewInterest.setTypeface(viewInterest.getTypeface(), Typeface.BOLD);
        }

        // Add the TextViews and the ImageView to the row and then add the row to the table
        interest_row.addView(viewCategory);
        interest_row.addView(viewInterest);
        interests_layout.addView(interest_row, new TableLayout.LayoutParams(
                TableLayout.LayoutParams.MATCH_PARENT,
                TableLayout.LayoutParams.WRAP_CONTENT));
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:
                onBackPressed();
                return true;

            default:
                // If we got here, the user's action was not recognized.
                // Invoke the superclass to handle it.
                return super.onOptionsItemSelected(item);
        }
    }

    @Override
    public void onBackPressed(){
        Intent intent=new Intent();
        intent.putExtra("match_id",match_id);
        intent.putExtra("match_name",match_name);
        setResult(1,intent);
        super.onBackPressed();
    }

}
