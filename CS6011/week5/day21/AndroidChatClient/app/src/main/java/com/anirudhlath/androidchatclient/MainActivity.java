package com.anirudhlath.androidchatclient;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.widget.EditText;

import com.google.android.material.textfield.TextInputEditText;

import org.w3c.dom.Text;

import java.io.IOException;

public class MainActivity extends AppCompatActivity {

    static String roomName = "";
    static String userName = "";
    EditText room;
    EditText user;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        room = findViewById(R.id.roomNameTE);
        user = findViewById(R.id.userNameTE);
        room.setOnClickListener(e -> {
            room.setText("");
        });
        user.setOnClickListener(e -> {
            user.setText("");
        });

    }

    public void joinRoom(View view) throws IOException {
        Intent intent = new Intent(this, ChatActivity.class);
        userName = user.getText().toString();
        roomName = room.getText().toString();
        String composedElement = "join " + roomName;
        Log.d("app.#MainActivity", "joinRoom: A user, " + userName + " has tried to join the room, " + roomName + ".");
        webSocketConnection wsc = new webSocketConnection();
        webSocketConnection.joinRoomString = composedElement;
        Log.d("app.#MainAcitivity", "joinRoom: SERVER RESPONSE: " + composedElement);
        startActivity(intent);
    }

}