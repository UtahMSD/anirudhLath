package com.anirudhlath.androidchatclient;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ListView;

import java.util.ArrayList;

public class ChatActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setTitle(MainActivity.roomName);
        setContentView(R.layout.activity_chat);
    }

    public void sendbutton(View view) {
        EditText chatMessageField = findViewById(R.id.chatMessageTE);
        String currentMessage = chatMessageField.getText().toString();
        ListView chatView = findViewById(R.id.chatViewLV);
        String currentUser = MainActivity.userName;
        String composedElement = currentUser + ": " + currentMessage;
        ArrayList<String> messagesArray = new ArrayList<>();
//        ArrayAdapter<String> messagesArrayAdapter = new ArrayAdapter<String>(this, chatView);
    }

}