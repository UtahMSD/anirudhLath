let socket = new WebSocket("ws://" + location.host);
let calculate = document.querySelector('#send');

socket.onopen = () => {
    console.log('Connection was opened!');
}
socket.onerror = (event) => {
    console.log('Connection encountered an error: ', event);
}
socket.onclose = () => {
    console.log('Connection was closed.');
}
socket.onmessage = (event) => {
    let result = document.querySelector("#result");
    result.innerHTML = event.data;
}

calculate.addEventListener("click", () => {
    let xTA = document.querySelector("#xTA");
    let yTA = document.querySelector("#yTA");


    let x  = Number(xTA.value);
    let y = Number(yTA.value);

    if(isNaN(x)) {
        alert("Please make sure you enter a number!");
        xTA.value = "";
        xTA.select();
        result.innerHTML = "";
    }

    if (isNaN(y)) {
        alert("Please make sure you enter a number!");
        yTA.value = "";
        yTA.select();
        result.innerHTML = "";
    }

    let response = x + " " + y;
    socket.send(response);

});