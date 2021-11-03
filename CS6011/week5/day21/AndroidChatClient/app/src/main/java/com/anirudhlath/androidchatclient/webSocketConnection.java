package com.anirudhlath.androidchatclient;

import android.util.Log;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.neovisionaries.ws.client.WebSocket;
import com.neovisionaries.ws.client.WebSocketAdapter;
import com.neovisionaries.ws.client.WebSocketException;
import com.neovisionaries.ws.client.WebSocketFactory;
import com.neovisionaries.ws.client.WebSocketFrame;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class webSocketConnection{

    static WebSocket ws_;
    static WebSocketFactory wsFactory_;
    static ArrayList<clientMessageObject> clientMessageObjects_ = new ArrayList<>();
    static String joinRoomString = "";
    GsonBuilder builder_ = new GsonBuilder();
    Gson gson_ = builder_.create();

    public webSocketConnection() throws IOException {
        wsFactory_ = new WebSocketFactory();
        ws_ = new WebSocketFactory().createSocket("ws://10.0.2.2:8080/index", 5000);
        builder_.setPrettyPrinting();
        ws_.connectAsynchronously();
        initiateListeners();
        Log.d("app.#WSC", "webSocketConnection: A websocket connection has been successfully initialised!");
    }

    public void handleTextMessage(String message) {
        clientMessageObject object = gson_.fromJson(message, clientMessageObject.class);
        ChatActivity.messages.add(object.user + ": " + object.message);
        clientMessageObjects_.add(object);
        Log.d("app.#WSC", "handleTextMessage: " + object);
    }

    public void initiateListeners() {
        ws_.addListener(new WebSocketAdapter() {
            @Override
            public void onConnected(WebSocket websocket, Map<String, List<String>> headers) throws Exception {
                Log.d("app.#WSC", "onConnected: The web socket connection was successful!");
                ws_.sendText(joinRoomString);
                //super.onConnected(websocket, headers);
            }

            @Override
            public void onConnectError(WebSocket websocket, WebSocketException exception) throws Exception {
                Log.d("app.#WSC", "onConnectError: Error connecting to the server.");
                Log.d("app.#WSC", "onConnectError: " + exception.getMessage());
                exception.printStackTrace();
                super.onConnectError(websocket, exception);
            }

            @Override
            public void onTextMessage(WebSocket websocket, String text) throws Exception {
                Log.d("app.#WSC", "onTextMessage: Received a text message.");
                handleTextMessage(text);

                ChatActivity.lv_.post(new Runnable() {
                    @Override
                    public void run() {
                        Log.d("app.#WSC", "run: RAN UPDATE");
                        Log.d("app.#WSC", "run: " + ChatActivity.messages);
                        ChatActivity.adapter_.notifyDataSetChanged();
                        ChatActivity.lv_.smoothScrollToPosition(ChatActivity.adapter_.getCount());
                    }
                });
            }

            @Override
            public void onFrameSent(WebSocket websocket, WebSocketFrame frame) throws Exception {
                Log.d("app.#WSC", "onFrameSent: A message was sent!");
                super.onFrameSent(websocket, frame);
            }
        });
    }


}
