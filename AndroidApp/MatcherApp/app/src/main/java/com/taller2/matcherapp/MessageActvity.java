package com.taller2.matcherapp;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.ListView;

import com.taller2.matcherapp.helper.Message;
import com.taller2.matcherapp.helper.MessagesListAdapter;

import java.util.ArrayList;

public class MessageActvity extends AppCompatActivity {

    private String match_id;
    private ArrayList<Message> listMessages;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_message);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        getSupportActionBar().setDisplayShowHomeEnabled(true);

        Intent intent = getIntent();
        match_id = intent.getStringExtra("Match ID");

        listMessages = new ArrayList<Message>();
        Message msg;
        for (int i=0; i < 10; i++){
            if(i%2 == 0){
                msg = new Message("Par","Hola",false);
            } else {
                msg = new Message("Impar","Yo",true);
            }
            listMessages.add(msg);
        }

        MessagesListAdapter adapter = new MessagesListAdapter(this, listMessages);
        ListView listViewMessages = (ListView) findViewById(R.id.messagesContainer);
        listViewMessages.setAdapter(adapter);

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_message, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.action_profile:
                Intent profile_intent = new Intent(MessageActvity.this, MatchActivity.class);
                profile_intent.putExtra("Match ID",match_id);
                startActivity(profile_intent);
                return true;

            default:
                // If we got here, the user's action was not recognized.
                // Invoke the superclass to handle it.
                return super.onOptionsItemSelected(item);
        }
    }

}
