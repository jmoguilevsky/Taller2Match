package com.taller2.matcherapp;

import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.support.v4.app.NavUtils;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Base64;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;
import android.widget.Toast;

import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.VolleyLog;
import com.android.volley.toolbox.JsonObjectRequest;
import com.taller2.matcherapp.app.AppConfig;
import com.taller2.matcherapp.app.AppController;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.ByteArrayOutputStream;
import java.util.HashMap;

public class ProfileActivity extends AppCompatActivity {

    private static final String TAG = ProfileActivity.class.getSimpleName();
    private ImageView profilePicture;
    private ProgressDialog pDialog;
    private ImageView addIcon;
    private static int RESULT_LOAD_IMG = 1;
    String imgDecodableString;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_profile);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        // Progress dialog
        pDialog = new ProgressDialog(this);
        pDialog.setCancelable(false);

        // Event when the profile picture is clicked: select a new picture from gallery.
        profilePicture = (ImageView) findViewById(R.id.match_image);
        profilePicture.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Create intent to Open Image applications like Gallery, Google Photos
                Intent galleryIntent = new Intent(Intent.ACTION_PICK,
                        android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
                // Start the Intent
                startActivityForResult(galleryIntent, RESULT_LOAD_IMG);
            }
        });

        // Create the interest table:
        // The interests table is populated dynamically, so we get its layout
        TableLayout interests_layout = (TableLayout) findViewById(R.id.interests_table);
        // Set the table's columns to be stretchable
        interests_layout.setStretchAllColumns(true);

        // Event when the Add Interest image is clicked: add a new interest
        addIcon = (ImageView) findViewById(R.id.match_add);
        addIcon.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Promt user to add Category and Interest using AlertDialog:

                // Create alert and set title and message.
                AlertDialog.Builder alert = new AlertDialog.Builder(v.getContext());
                alert.setTitle("Add Category and Interest");
                alert.setMessage("Please complete the following fields");

                // Create a layout that will have EditText fields.
                Context context = v.getContext();
                LinearLayout layout = new LinearLayout(context);
                layout.setOrientation(LinearLayout.VERTICAL);
                // Create and add the Category field to the layout
                final EditText categoryBox = new EditText(context);
                categoryBox.setHint("Category");
                layout.addView(categoryBox);
                // Createa and add the interest field to the layout
                final EditText interestBox = new EditText(context);
                interestBox.setHint("Interest");
                layout.addView(interestBox);
                // Add the layout to the alert
                alert.setView(layout);

                // Define behaviour for click on positive button
                alert.setPositiveButton("Ok", new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int whichButton) {
                        // Get input strings and add a row to the table with category and interest.
                        String category = categoryBox.getText().toString();
                        String interest = interestBox.getText().toString();
                        add_row_interests_table(category, interest);
                    }
                });
                // Define behaviour for click on negative button
                alert.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int whichButton) {
                        // Canceled.
                    }
                });

                alert.show();
            }
        });

        add_row_interests_table("Music/band","Radiohead");
        add_row_interests_table("Music/band","Metallica");
        add_row_interests_table("Food","Rice");
    }

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

                int columnIndex = cursor.getColumnIndex(filePathColumn[0]);
                imgDecodableString = cursor.getString(columnIndex);
                cursor.close();
                ImageView imgView = (ImageView) findViewById(R.id.match_image);
                // Set the Image in ImageView after decoding the String
                Bitmap map = BitmapFactory.decodeFile(imgDecodableString);
                imgView.setImageBitmap(map);

                // Send the new Picture to the App server:
                // Tag used to cancel the request
                String tag_json_req = "req_update_pic";

                pDialog.setMessage("Uploading new picture...");
                showDialog();

                String picture_string = getStringImage(map);
                // Post params to be sent to the server: just the picture in base_64 string
                HashMap<String, String> params = new HashMap<String, String>();
                params.put("picture", picture_string);

                // Create the request for a JSONObject
                JsonObjectRequest jsonObjReq = new JsonObjectRequest(Request.Method.POST,
                        AppConfig.URL_REGISTER, new JSONObject(params),
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
                        hideDialog();
                    }

                });

                // Adding request to request queue
                AppController.getInstance().addToRequestQueue(jsonObjReq, tag_json_req);

            } else {
                Toast.makeText(this, "You haven't picked Image",
                        Toast.LENGTH_LONG).show();
            }
        } catch (Exception e) {
            Toast.makeText(this, "Something went wrong", Toast.LENGTH_LONG)
                    .show();
        }

    }

    // Function that adds rows with the format Category /I nterest / Trash can icon to the table.
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

        TextView viewInterest = new TextView(this);
        viewInterest.setText(interest);

        ImageView viewTrashCan = new ImageView(this);
        viewTrashCan.setImageDrawable(getResources().getDrawable(R.drawable.ic_delete_black_18dp));
        // Set the trash icon to delete the interest when clicked
        viewTrashCan.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // This is the parent row of the trash can icon clicked:
                View row = (View) v.getParent();
                // This is the parent table of the row:
                ViewGroup table = (ViewGroup) row.getParent();
                // delete the row and invalidate the view so it gets redrawn.
                table.removeView(row);
                table.invalidate();
                // TODO decirle al server que se elimino un interes.
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
        Log.d(TAG,"volviendo a main act");
        NavUtils.navigateUpFromSameTask(this);
        finish();
        return;
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_profile, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.action_settings:
                Log.d(TAG,"action settings");
                return true;

            case android.R.id.home:
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

    public String getStringImage(Bitmap bmp){
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        bmp.compress(Bitmap.CompressFormat.JPEG, 100, baos);
        byte[] imageBytes = baos.toByteArray();
        String encodedImage = Base64.encodeToString(imageBytes, Base64.DEFAULT);
        return encodedImage;
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
