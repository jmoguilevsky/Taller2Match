package com.taller2.matcherapp;

import android.content.Intent;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.os.Message;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v4.app.NavUtils;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Toast;

import com.taller2.matcherapp.helper.CustomListAdapter;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;

public class ChatActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chat);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        getSupportActionBar().setDisplayShowHomeEnabled(true);

        String response = "[{\n" +
                "\"id\":\"15\",\n" +
                "\"name\":\"User 1\"\n" +
                "},{\n" +
                "\"id\":\"99\",\n" +
                "\"name\":\"User 2\"\n" +
                "},{\n" +
                "\"id\":\"32\",\n" +
                "\"name\":\"User 3\"\n" +
                "}]";

        // Create a hashmap that will have (position,id) as the (key,value) pairs
        final HashMap matches = new HashMap<String, String>();
        // Create a list with the matches' names
        List<String> names = new ArrayList<String>();
        try {
            JSONArray matches_array = new JSONArray(response);
            for (int i = 0; i < matches_array.length(); i++){
                JSONObject match = matches_array.getJSONObject(i);
                String id = match.getString("id");
                String name = match.getString("name");
                matches.put(i,id);
                names.add(i,name);
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }

        // Create a custom list adapter to populate the list of matches.
        String[] names_array = names.toArray(new String[names.size()]);
        CustomListAdapter adapter = new CustomListAdapter(this,names_array);
        ListView listView = (ListView) findViewById(R.id.chat_list);
        listView.setAdapter(adapter);
        // Set the click listener to start a conversation when a match is clicked.
        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view,
                                    int position, long id) {
                String match_id = (String) matches.get(position);
                Intent intent = new Intent(ChatActivity.this, MessageActvity.class);
                intent.putExtra("Match ID",match_id);
                Log.d("CHAT to MESSAGE",match_id);
                startActivity(intent);
            }
        });
    }
}
