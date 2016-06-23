package com.taller2.matcherapp;

import android.app.ProgressDialog;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;

import com.taller2.matcherapp.helper.Message;
import com.taller2.matcherapp.helper.MessagesListAdapter;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;

public class MessageActvity extends AppCompatActivity {

    private String match_id;
    private Button btnSend;
    private ArrayList listMessages;
    private EditText textField;
    private MessagesListAdapter adapter;

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
        textField = (EditText) findViewById(R.id.messageEdit);

        String filePath = "data/data/com.taller2.matcherapp/"+match_id+".txt";
        File file = new File(filePath);
        if (file.exists()){
            int length = (int) file.length();
            byte[] bytes = new byte[length];
            try {
                FileInputStream fis = new FileInputStream(file);
                fis.read(bytes);
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
            String contents = new String(bytes);
            parseContents(contents);
        }
        else {
            try {
                file.createNewFile();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        listMessages = new ArrayList<>();
        Message msg;
        Message msg2;
        for (int i=0; i < 12; i++){
            if(i%2 == 0){
                msg = new Message("Par","Hola",false);
                msg2 = new Message("Par","Hola2",false);
            } else {
                msg = new Message("Impar","HOLIS",true);
                msg2 = new Message("Impar","Hola2",true);
            }
            listMessages.add(msg);
            listMessages.add(msg2);
        }

        adapter = new MessagesListAdapter(this, listMessages);
        final ListView listViewMessages = (ListView) findViewById(R.id.messagesContainer);
        listViewMessages.setAdapter(adapter);
        listViewMessages.setSelection(adapter.getCount()-1);

        btnSend = (Button)findViewById(R.id.chatSendButton);
        // Register the onClick listener with the implementation above
        btnSend.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v)
            {
                String text = textField.getText().toString();
                Message msg = new Message(match_id,text,true);
                listMessages.add(msg);
                adapter.notifyDataSetChanged();
            }
        });
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

    public void parseContents(String contents){
        // TODO
    }
}
