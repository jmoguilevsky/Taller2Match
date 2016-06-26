package com.taller2.matcherapp;

import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.support.v4.app.NavUtils;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.Spinner;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;
import android.widget.Toast;

import com.android.volley.AuthFailureError;
import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.VolleyLog;
import com.android.volley.toolbox.JsonObjectRequest;
import com.taller2.matcherapp.app.AppController;
import com.taller2.matcherapp.helper.GPSTracker;
import com.taller2.matcherapp.helper.SQLiteHandler;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ProfileActivity extends AppCompatActivity {

    private static final String TAG = ProfileActivity.class.getSimpleName();
    private ImageView viewProfilePicture;
    private ProgressDialog pDialog;
    private ImageView addIcon;
    private Button btnLocation;
    private static int RESULT_LOAD_IMG = 1;
    private static final int PROFILE_IMAGE_SIZE = 280;
    int SELECT_PICTURE = 2;
    private boolean isProfileModified;
    String imgPath;
    private SQLiteHandler db;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_profile);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        getSupportActionBar().setDisplayShowHomeEnabled(true);
        getSupportActionBar().setTitle("Your profile");
        isProfileModified = false;

        // Get the database handler
        db = new SQLiteHandler(getApplicationContext());
        HashMap<String, String> user = db.getUserDetails();

        // Progress dialog
        pDialog = new ProgressDialog(this);
        pDialog.setCancelable(false);

        // Populate de profile picture with the image saved as base_64 in the database.
        viewProfilePicture = (ImageView) findViewById(R.id.match_image);
        String profile_photo_str = user.get("photo");
        Bitmap profile_photo_map = AppController.getInstance().getBitmapImage(profile_photo_str);
        if (profile_photo_map != null){
            viewProfilePicture.setImageBitmap(profile_photo_map);
        }

        // Event when the profile picture is clicked: select a new picture from gallery.
        viewProfilePicture.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Create intent to Open Image applications like Gallery, Google Photos
                // See the method onActivityResult below

                changeProfilePhoto();

                /*Intent galleryIntent = new Intent(Intent.ACTION_PICK,
                        android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
                // Start the Intent
                startActivityForResult(galleryIntent, RESULT_LOAD_IMG);*/
            }
        });



        // Create the interest table:
        // The interests table is populated dynamically, so we get its layout
        TableLayout interests_layout = (TableLayout) findViewById(R.id.interests_table);
        // Set the table's columns to be stretchable
        interests_layout.setStretchAllColumns(true);
        // Populate the interests table with the values in the database
        try {
            // Create de JSONObject, get its array with the interests
            JSONArray interests_array = new JSONArray(user.get("interests"));
            Log.d("Profile lee de la db:",interests_array.toString());
            // Iterate over the interests in the array, whose form is (category,value)
            Log.d("length",String.valueOf(interests_array.length()));
            for (int i=0; i < interests_array.length(); i++){
                // Add each interest to the table
                JSONObject interest = interests_array.getJSONObject(i);
                String category = interest.getString("category");
                String value = interest.getString("value");
                add_row_interests_table(category,value);
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }

        btnLocation = (Button) findViewById(R.id.btnLocation);
        btnLocation.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // create class object
                GPSTracker gps = new GPSTracker(ProfileActivity.this);
                double latitude = 0;
                double longitude = 0;
                // check if GPS enabled
                if(gps.canGetLocation()){
                    latitude = gps.getLatitude();
                    longitude = gps.getLongitude();
                    // \n is for new line
                    Toast.makeText(getApplicationContext(), "Location updated!", Toast.LENGTH_LONG).show();
                }else{
                    // can't get location
                    // GPS or Network is not enabled
                    // Ask user to enable GPS/network in settings
                    gps.showSettingsAlert();
                }
                JSONObject location = new JSONObject();
                try {
                    location.put("latitude",latitude);
                    location.put("longitude",longitude);
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                db.update_value("location",location.toString());
                isProfileModified = true;
            }
        });

        // Event when the Add Interest image is clicked: add a custom category and interest
        addIcon = (ImageView) findViewById(R.id.match_add);
        addIcon.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Promt user to add Category and Interest using AlertDialog:

                // Create alert and set title and message.
                AlertDialog.Builder alert = new AlertDialog.Builder(v.getContext());
                alert.setTitle("Add Category and Interest");
                alert.setMessage("Select an existing category or add a new one");

                // Create a layout that will have EditText fields.
                final Context context = v.getContext();
                final LinearLayout layout = new LinearLayout(context);
                layout.setOrientation(LinearLayout.VERTICAL);
                // TODO poner limite a la cantidad de texto que puede ingresar el usuario.
                // Create the add custom category field, but we dont add it to the layout yet
                final EditText categoryBox = new EditText(context);
                categoryBox.setHint("Category");
                layout.addView(categoryBox,0);
                // Create the add interest field, but we dont add it to the layout yet
                final EditText interestBox = new EditText(context);
                interestBox.setHint("Interest");
                layout.addView(interestBox,0);
                // Create a spinner menu with the category options
                List<String> spinnerArray =  new ArrayList<String>();
                // TODO pedir al server lista de categorias.
                spinnerArray.add("music");
                spinnerArray.add("music/band");
                spinnerArray.add("outdoors");
                spinnerArray.add("sport");
                spinnerArray.add("sex");
                spinnerArray.add("travel");
                spinnerArray.add("food");
                spinnerArray.add("Add new category");
                Spinner spinner = new Spinner(context);
                ArrayAdapter<String> spinnerArrayAdapter = new ArrayAdapter<>(context, android.R.layout.simple_spinner_item, spinnerArray);
                spinnerArrayAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
                spinner.setAdapter(spinnerArrayAdapter);
                layout.addView(spinner,0);
                // Create a onClick listener
                spinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener(){
                    public void onItemSelected(AdapterView<?> parent, View view, int position, long id)
                    {
                        String selectedItem = parent.getItemAtPosition(position).toString();
                        if(selectedItem.equals("Add new category"))
                        {
                            // Add the custom category field to the layout
                            categoryBox.setText("");
                            layout.addView(categoryBox,1);
                        } else {
                            layout.removeView(categoryBox);
                            categoryBox.setText(selectedItem);
                        }
                    } // to close the onItemSelected
                    public void onNothingSelected(AdapterView<?> parent)
                    {
                        categoryBox.setText("");
                    }
                });
                // Add the layout to the alert
                alert.setView(layout);

                // Define behaviour for click on positive button
                alert.setPositiveButton("Ok", new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int whichButton) {
                        // Get input strings and add a row to the table with category and interest.
                        String category = categoryBox.getText().toString();
                        String interest = interestBox.getText().toString();
                        if (category.isEmpty() || interest.isEmpty() ){
                            Toast.makeText(context,"One of the fields was emtpy! Try again",Toast.LENGTH_LONG).show();
                        } else {
                            add_row_interests_table(category, interest);
                            // The profile was modified
                            isProfileModified = true;
                        }
                    }
                });
                // Define behaviour for click on negative button
                alert.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int whichButton) {
                        Toast.makeText(context,"Canceled",Toast.LENGTH_LONG).show();
                    }
                });

                alert.show();
            }
        });
    }

    /*
    // Here we define the behaviour when the gallery activity finishes.
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        try {
            // When an Image is picked
            if (requestCode == RESULT_LOAD_IMG && resultCode == RESULT_OK
                    && null != data) {
                // Get the Image from data
                Uri selectedImage = data.getData();
                String[] filePathColumn = { MediaStore.Images.Media.DATA };
                // Get the cursor
                Cursor cursor = getContentResolver().query(selectedImage,
                        filePathColumn, null, null, null);
                // Move to first row
                cursor.moveToFirst();
                // Select the column that has de image string and get it.
                int columnIndex = cursor.getColumnIndex(filePathColumn[0]);
                imgPath = cursor.getString(columnIndex);
                cursor.close();
                // Get the view that will display the image
                viewProfilePicture = (ImageView) findViewById(R.id.match_image);
                // Set the Image in ImageView after decoding the String
                Bitmap map = BitmapFactory.decodeFile(imgPath);
                String imgDecodableString = AppController.getInstance().getStringImage(map);
                Bitmap picture_map = AppController.getInstance().getBitmapImage(imgDecodableString);
                viewProfilePicture.setImageBitmap(picture_map);
                // The profile was modified
                isProfileModified = true;
                // Update the local database
                db.update_value("photo",imgDecodableString);

            } else {
                Toast.makeText(this, "You haven't picked Image",
                        Toast.LENGTH_LONG).show();
            }
        } catch (Exception e) {
            Toast.makeText(this, "Something went wrong", Toast.LENGTH_LONG)
                    .show();
        }

    }*/

    // Function that adds rows with the format Category / Interest / Trash can icon to the table.
    public void add_row_interests_table(String category, String interest){
        // The interests table is populated dynamically, so we get its layout
        TableLayout interests_layout = (TableLayout) findViewById(R.id.interests_table);
        // Create a new row to add to the table, set the row's layout.
        TableRow interest_row = new TableRow(this);
        interest_row.setLayoutParams(new TableRow.LayoutParams(TableRow.LayoutParams.MATCH_PARENT, TableRow.LayoutParams.WRAP_CONTENT));
        interest_row.setBackgroundColor(Color.LTGRAY);
        // Each row will have 3 columns: Category / Interest / Delete icon
        // which will be TextView / TextView / ImageView. Set them up:
        TextView viewCategory = new TextView(this);
        viewCategory.setText(category);
        viewCategory.setTextSize(22);

        TextView viewInterest = new TextView(this);
        viewInterest.setText(interest);
        viewInterest.setTextSize(22);

        ImageView viewTrashCan = new ImageView(this);
        viewTrashCan.setImageDrawable(getResources().getDrawable(R.drawable.ic_delete_black_18dp));

        Bitmap bMap = BitmapFactory.decodeResource(getResources(), R.drawable.ic_delete_black_24dp);
        Bitmap bMapScaled = Bitmap.createScaledBitmap(bMap,pxFromDp(28),pxFromDp(28), true);
        viewTrashCan.setImageBitmap(bMapScaled);
        // Set the trash icon to delete the interest when clicked
        viewTrashCan.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // This is the parent row of the trash can icon clicked:
                View row = (View) v.getParent();
                // This is the parent table of the row:
                ViewGroup table = (ViewGroup) row.getParent();
                isProfileModified = true;
                // delete the row and invalidate the view so it gets redrawn.
                table.removeView(row);
                table.invalidate();
            }
        });
        // Add the TextViews and the ImageView to the row and then add the row to the table
        interest_row.addView(viewCategory);
        interest_row.addView(viewInterest);
        interest_row.addView(viewTrashCan);
        interests_layout.addView(interest_row, new TableLayout.LayoutParams(
                TableLayout.LayoutParams.MATCH_PARENT,
                TableLayout.LayoutParams.WRAP_CONTENT));
    }

    @Override
    public void onBackPressed() {
        update_profile();
        Log.d(TAG,"volviendo a main act");
        NavUtils.navigateUpFromSameTask(this);
        finish();
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:
                update_profile();
                Log.d(TAG,"volviendo a main act");
                NavUtils.navigateUpFromSameTask(this);
                finish();
                return true;

            default:
                // If we got here, the user's action was not recognized.
                // Invoke the superclass to handle it.
                return super.onOptionsItemSelected(item);
        }
    }

    public void update_profile(){
        // Method that commmits to the server the changes in the user profile, if any.
        // If the commit request is successful, the changes are committed locally too.
        // On error, the changes are discarded.
        if (isProfileModified){
            // We create the JSONObject defined in the API (check documentation) to be PUT to the server.
            final HashMap<String, String> user = db.getUserDetails();

            JSONObject json_param_user = new JSONObject();
            JSONObject json_user = new JSONObject();
            try{
                json_user.put("name",user.get("name"));
                json_user.put("email",user.get("email"));
                json_user.put("alias",user.get("alias"));
                json_user.put("sex",user.get("gender"));
                // We get the current profile picture
                Drawable pic = viewProfilePicture.getDrawable();
                Bitmap bitmap = ((BitmapDrawable)pic).getBitmap();
                String pic_string = AppController.getInstance().getStringImage(bitmap);
                json_user.put("photo_profile",pic_string);
                // We read the rows of the interest table and load them to a JSONArray
                JSONArray json_arr_interest = new JSONArray();
                TableLayout interests_layout = (TableLayout) findViewById(R.id.interests_table);
                for(int i = 0, j = interests_layout.getChildCount(); i < j; i++) {
                    View view = interests_layout.getChildAt(i);
                    if (view instanceof TableRow) {
                        TableRow row = (TableRow) view;
                        JSONObject dupla = new JSONObject();
                        TextView viewCat = (TextView) row.getChildAt(0);
                        TextView viewInt = (TextView) row.getChildAt(1);
                        dupla.put("category",viewCat.getText().toString());
                        dupla.put("value",viewInt.getText().toString());
                        json_arr_interest.put(dupla);
                    }
                }
                db.update_value("interests",json_arr_interest.toString());
                json_user.put("interests",json_arr_interest);
                JSONObject loc = new JSONObject(user.get("location"));
                json_user.put("location",loc);
                json_param_user.put("user",json_user);
            } catch (JSONException e) {
                e.printStackTrace();
            }
            // Tag used to cancel the request
            String tag_json_req = "req_update_profile";

            pDialog.setMessage("Updating profile ...");
            showDialog();

            // Create a PUT request, send JSONObject.
            // On success expect an empty JSON
            // On failute expect a JSON with an error field
            JsonObjectRequest jsonObjReq = new JsonObjectRequest(Request.Method.PUT,
                    AppController.getInstance().getUpdateProfile(), json_param_user,
                    new Response.Listener<JSONObject>() {

                        @Override
                        public void onResponse(JSONObject response) {
                            Log.d(TAG, response.toString());
                            Toast.makeText(getApplicationContext(),
                                    "Profile update successful!", Toast.LENGTH_LONG).show();
                            hideDialog();
                        }
                    }, new Response.ErrorListener() {

                @Override
                public void onErrorResponse(VolleyError error) {
                    VolleyLog.d(TAG, "Error: " + error.getMessage());
                    Log.d(TAG, error.toString());
                    hideDialog();
                }

            }){
                @Override
                public Map<String, String> getHeaders() throws AuthFailureError {
                    Map<String, String> params = new HashMap<>();
                    params.put("Authorization", user.get("token"));
                    return params;
                }
            };

            // Adding request to request queue
            AppController.getInstance().addToRequestQueue(jsonObjReq, tag_json_req);
            hideDialog();
        }
        else {
            Log.d(TAG,"Profile was not modified.");
        }
    }

    private void changeProfilePhoto(){
        Log.d(TAG,"Change profile pic");
        Intent imgDownload = new Intent(Intent.ACTION_PICK, MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
        imgDownload.putExtra("crop", "true");
        imgDownload.putExtra("aspectX", 1);
        imgDownload.putExtra("aspectY", 1);
        imgDownload.putExtra("outputX",PROFILE_IMAGE_SIZE);
        imgDownload.putExtra("outputY",PROFILE_IMAGE_SIZE);
        imgDownload.putExtra("return-data", true);
        startActivityForResult(imgDownload,SELECT_PICTURE);
    }

    public void onActivityResult(int requestCode, int resultCode, Intent data){
        super.onActivityResult(requestCode,resultCode,data);
        if (requestCode == SELECT_PICTURE && resultCode == RESULT_OK && data!=null){
            Bundle extras = data.getExtras();
            Bitmap image = extras.getParcelable("data");
            viewProfilePicture.setImageBitmap(image);
            Log.d(TAG,"Profile picture modified");

            String imgDecodableString = AppController.getInstance().getStringImage(image);
            // The profile was modified
            isProfileModified = true;
            // Update the local database
            db.update_value("photo",imgDecodableString);
        }
    }

    private void showDialog() {
        if (!pDialog.isShowing())
            pDialog.show();
    }

    private void hideDialog() {
        if (pDialog.isShowing())
            pDialog.dismiss();
    }

    private int pxFromDp(float dp)
    {
        return (int) (dp * getResources().getDisplayMetrics().density);
    }

    private int dpFromPx(float px)
    {
        return (int) (px / getResources().getDisplayMetrics().density);
    }
}