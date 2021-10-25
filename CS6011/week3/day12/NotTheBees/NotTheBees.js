'use strict';

// Variables
let body = document.body;
let myDiv = document.getElementById("canvas-container");
let potCanvas = document.getElementById('potWindow');
let beeCanvas = document.getElementById('beeWindow');
let potContext = potCanvas.getContext('2d');
let beeContext = beeCanvas.getContext('2d');
let width = potCanvas.width;
let height = potCanvas.height;

let honeyImg = new Image();
let beeImg = new Image();

let frameCount = 0;
let stepCounter = 0;

let potX = 250;
let potY = 250;
let dx = 5;
let dy = 5;

let gameOver = false;

let bees = [
    {
        'x': 0,
        'y': 0,
    },
    {
        'x': 200,
        'y': 50,
    },
    {
        'x': 670,
        'y': 100,
    },
    {
        'x': 470,
        'y': 100,
    },
    {
        'x': 620,
        'y': 170,
    },
    {
        'x': 1270,
        'y': 190,
    },
];

// Set Attributes
honeyImg.src = 'images/honeypot.png';
beeImg.src = 'images/bee-up.png';

// Set Styles
beeCanvas.style.backgroundColor = 'lightblue';
beeCanvas.style.marginTop = '5px';
potCanvas.style.marginTop = '5px';



// On Window Load
window.onload = function() {
    drawHoneyImage();
}

// Main Loop
potCanvas.addEventListener('mousemove', function (e) {
    if(!gameOver) {
        updateHoneyImg(e);
    } else {
        potContext.clearRect(0,0,width, height);
        body.innerHTML = '<h1 style="text-align: center">GAME OVER!</h1>';

    }
})
update();

// Functions
function drawHoneyImage() {
    honeyImg.onload = function() {
        potContext.drawImage(honeyImg, potX, potY, 70, 70);
    }
}

function updateHoneyImg(e) {
    potContext.clearRect(0,0, width, height);
    if(e != null) {
        potX = e.offsetX;
        potY = e.offsetY;
        potContext.drawImage(honeyImg, potX, potY, 70, 70);
    }
}

function update() {
    frameCount++;
    if (frameCount % 15 === 0) {
        stepCounter++;
    }
    if (stepCounter % 2 === 0) {
        beeImg.src = 'images/bee-down.png';
    } else {
        beeImg.src = 'images/bee-up.png';
    }

    for(let bee of bees) {
        let distanceFromPot = Math.sqrt(Math.pow(Math.abs(potX - bee.x), 2) + Math.pow(Math.abs(potY - bee.y), 2));
        if(distanceFromPot > 30.0 && frameCount % 10 === 0) {
            if(potX > bee.x) {
                bee.x += dx;
            }if(potX < bee.x) {
                bee.x -= dx;
            }if(potY > bee.y) {
                bee.y += dy;
            }if(potY < bee.y) {
                bee.y -= dy;
            }
            updateBeeImage(bee.x, bee.y);
        } else if ( distanceFromPot < 25.0 && frameCount > 60 ){
            console.log('game over');
            beeCanvas.style.backgroundColor = 'red';
            body.style.backgroundColor = 'red';
            beeContext.clearRect(0,0,width,height);
            gameOver = true;
            break;
        }

    }
    if (!gameOver) {
        window.requestAnimationFrame(update);
    }

}


function updateBeeImage(x, y) {
    beeContext.clearRect(x - dx,y - dy,x + 25 + dx, y + 25 + dy);
    beeContext.drawImage(beeImg, x, y, 25, 25);

}

