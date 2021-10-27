"use strict";

let xTA = document.querySelector("#xTA");
let yTA = document.querySelector("#yTA");
let calculate = document.querySelector("#send");
let result = document.querySelector("#result");

calculate.addEventListener("click", () => {
    console.log("button was pressed!")
    let x  = Number(xTA.value);
    let y = Number(yTA.value);
    let isNumber = false;

    if(isNaN(x)) {
        alert("Please make sure you enter a number!");
        xTA.value = "";
        xTA.select();
        isNumber = false;
        result.innerHTML = "";
    } else {
        isNumber = true;
    }

    if (isNaN(y)) {
        alert("Please make sure you enter a number!");
        yTA.value = "";
        yTA.select();
        isNumber = false;
        result.innerHTML = "";
    } else {
        isNumber = true;
    }

    // Use AJAX to get the result from the server.
    let request = new XMLHttpRequest();
    request.open("GET", "http://localhost:8080/calculate?x=" + x + "&y=" + y);
    request.addEventListener( "load", () => {
        console.log("The request was loaded!");
        console.log(this.responseText);
        result.innerHTML = this.responseText;

    });
    request.addEventListener("error", () => {
        console.log("An error occurred.");

    });
    request.send();

    /*if (isNumber) {
        result.innerHTML = x + y;
    }*/
});