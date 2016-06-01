package com.taller2.matcherapp;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.taller2.matcherapp.helper.SQLiteHandler;
import com.taller2.matcherapp.helper.SessionManager;

import java.util.HashMap;

public class MainActivity extends AppCompatActivity {

    private TextView txtEmail;
    private ImageView imgMatch;
    private Button btnFind;
    private ImageView iconHeart;
    private ImageView iconCross;
    private int LIKE_MATCH = 1;
    private int DISLIKE_MATCH = 2;

    private SQLiteHandler db;
    private SessionManager session;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar myToolbar = (Toolbar) findViewById(R.id.my_toolbar);
        setSupportActionBar(myToolbar);

        // Obtain and assign views
        txtEmail = (TextView) findViewById(R.id.email);
        imgMatch = (ImageView) findViewById(R.id.match_image);
        btnFind = (Button) findViewById(R.id.btnFind);
        iconHeart = (ImageView) findViewById(R.id.match_accept);
        iconCross = (ImageView) findViewById(R.id.match_reject);

        // SqLite database handler
        db = new SQLiteHandler(getApplicationContext());

        // session manager
        session = new SessionManager(getApplicationContext());
        if (!session.isLoggedIn()) {
            logoutUser();
        }

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
        btnFind.setOnClickListener(match_clickListener);

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

        db.deleteUsers();

        // Launching the login activity
        Intent intent = new Intent(MainActivity.this, LoginActivity.class);
        startActivity(intent);
        finish();
    }

    private void findMatch(){
        imgMatch.setImageResource(R.drawable.sans);
        imgMatch.setVisibility(View.VISIBLE);
    }

    private void acceptMatch(){
        // TODO
    }

    private void rejectMatch(){
        // TODO
    }

    private void react_to_match(int reaction){
        if (reaction == LIKE_MATCH){

        }
        else if (reaction == DISLIKE_MATCH){

        }
    }
}
