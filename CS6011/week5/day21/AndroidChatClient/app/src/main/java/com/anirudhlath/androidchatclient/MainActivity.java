package com.anirudhlath.androidchatclient;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.widget.EditText;

import com.google.android.material.textfield.TextInputEditText;

import org.w3c.dom.Text;

public class MainActivity extends AppCompatActivity {

    static String roomName = "";
    static String userName = "";


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void joinRoom(View view) {
        Intent intent = new Intent(this, ChatActivity.class);
        EditText room = findViewById(R.id.roomNameTE);
        EditText user = findViewById(R.id.userNameTE);
        userName = user.getText().toString();
        roomName = room.getText().toString();
        System.out.println("Clicked the button!");
        startActivity(intent);
    }

}