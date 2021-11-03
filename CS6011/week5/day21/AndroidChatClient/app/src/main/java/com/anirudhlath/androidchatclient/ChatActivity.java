package com.anirudhlath.androidchatclient;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ListView;

import java.io.IOException;
import java.util.ArrayList;

public class ChatActivity extends AppCompatActivity {

    static ArrayList<String> messages = new ArrayList<>();
    static ListView lv_;
    static ArrayAdapter adapter_;
    EditText chatMessageField;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setTitle(MainActivity.roomName);
        setContentView(R.layout.activity_chat);
        chatMessageField = findViewById(R.id.chatMessageTE);
        chatMessageField.setOnClickListener(e -> chatMessageField.setText(""));

    }

    public void sendbutton(View view) {
        String currentMessage = chatMessageField.getText().toString();
        lv_ = findViewById(R.id.chatViewLV);
        String currentUser = MainActivity.userName;
        String composedElement = currentUser + " " + currentMessage;
        webSocketConnection.ws_.sendText(composedElement);
        Log.d("app.#ChatActivity", "sendbutton: A message has been sent to the server!");
        adapter_ = new ArrayAdapter(this, android.R.layout.simple_list_item_1, messages);
        lv_.setAdapter(adapter_);
    }

}