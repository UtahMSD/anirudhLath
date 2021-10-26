"use strict";

let socket = new WebSocket("ws://localhost:8080");
let sendButton = document.querySelector("#sendMessageButton");

sendButton.addEventListener("click", () => {
    let userName = document.querySelector("#username");
    let chatRoom = document.querySelector("#chatroom");
    let message = document.querySelector("#message");
    let innerData = "<p>" + userName.value + ": " + message.value + "</p>";

    socket.send(innerData);

    message.value = "";

    console.log("Message Sent");
});

socket.onopen = (event) => {
    console.log("WebSocket connection is open!");
};

socket.onclose = (event) => {
    console.log("WebSocket connection is closed!");
};

socket.onerror = (event) => {
    console.log("WebSocket connection has an error: ", event);
};

socket.onmessage = function (event) {
    console.log("WebSocket connection has received a message!");
    let chat = document.querySelector("#chatbox");
    document.body.innerHTML += event.data;
};

