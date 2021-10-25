'use strict';
// Variables
let body = document.body;
let table = document.createElement('table');
let selected = false;
let selectedCount = 0;

// Styling
table.style.alignContent = 'center';
table.style.textAlign = 'center';
table.style.marginLeft = 'auto';
table.style.marginRight = 'auto';
table.style.padding = '10px';
body.style.fontFamily = "'Helvetica', serif";



function createMultiplicationTable() {
    let headerRow = document.createElement('tr');

    for(let i = 0; i < 11; i++) {
        let theNumber = document.createElement('th');
        let deadCell = document.createElement('th');
        theNumber.style.padding = '10px';
        theNumber.style.backgroundColor = 'lightblue';
        if (i === 0) {
            headerRow.appendChild(deadCell);
        } else {
            theNumber.textContent = i.toString();
            headerRow.appendChild(theNumber);
            headerRow.appendChild(theNumber);
        }
    }



    for(let i = 0; i < 10; i++) {
        let row = document.createElement('tr');


        for(let j = 0; j < 10; j++) {
            let theMultiple = document.createElement('th');
            let theProduct = document.createElement('td');
            theProduct.style.padding = '10px';
            theMultiple.style.padding = '10px';
            theMultiple.style.backgroundColor = 'lightblue';
            let product = 0;
            if (j === 0) {
                theMultiple.textContent = (i + 1).toString();
                row.appendChild(theMultiple);
            }
            product = ((i + 1) * (j + 1));
            theProduct.textContent = product.toString();
            row.appendChild(theProduct);
        }
        table.appendChild(row);
        /*th.textContent = number.toString();
        if (i === 0) {
            tr.appendChild(deadCell);
            table.appendChild(tr);
        }
        tr.appendChild(th);
        table.appendChild(tr);
        for (let j = 0; j < 10; j++) {
            let multiple = j + 1;

            thMultiple.textContent = multiple.toString();
            tr.appendChild(thMultiple);
        }
        for (let j = 0; j < 10; j++) {

        }
        body.appendChild(table);*/
    }
    table.appendChild(headerRow);
    body.appendChild(table);
}


function handleInteraction() {
    let allTheProducts = document.querySelectorAll('td');
    for (let theProduct of allTheProducts) {
        let hoverCheck = false;
        theProduct.addEventListener('mouseover', function () {
            theProduct.style.backgroundColor = 'lightgreen';
            hoverCheck = true;
        });

        theProduct.addEventListener('mouseout', function () {

            if (!hoverCheck && selected) {
                let allProducts = document.querySelectorAll('td');
                for (let product of allProducts) {
                    product.style.backgroundColor = '';
                    hoverCheck = false;
                }
            }
            else {
                theProduct.style.backgroundColor = '';
            }
        });

        theProduct.addEventListener('click', function () {
            if (!selected && selectedCount === 0) {
                console.log('fired');
                console.log(selectedCount);
                theProduct.style.backgroundColor = 'pink';
                selected = true;

                selectedCount = selectedCount + 1;
            } else if (!selected && selectedCount > 0) {
                console.log('fired2');
                console.log(selectedCount);
                theProduct.style.backgroundColor = 'pink';
                selected = false;
                selectedCount--;
                let allProducts = document.querySelectorAll('td');
                for (let product of allProducts) {
                    if (product !== theProduct) {
                        product.style.backgroundColor = '';
                    }
                }

            } else {
                console.log(selectedCount);
                selected = false;
            }
        });
    }
}

function handleObnoxious() {
    let colorValue = 0;
    let reverse = false;
    window.setInterval(function () {
        body.style.backgroundColor = 'rgb(255,0,'+ colorValue + ')';

        if (colorValue > 255) {
            reverse = true;
        }
        else if (colorValue < 0) {
            reverse = false;
        }

        if(!reverse) {
            colorValue += 5;
        }
        else {
            colorValue -= 5;
        }

        console.log('fired obnoxious');
        }, 100);
}

function obnoxious() {
    let clickMe = document.createElement('h3');
    clickMe.textContent = 'Click Me!';
    body.appendChild(clickMe);
    clickMe.style.fontFamily = "'Arial Black',serif";
    clickMe.style.textAlign = 'center';
    clickMe.style.marginTop = '100px';
    clickMe.addEventListener('click', handleObnoxious);
}

createMultiplicationTable();
handleInteraction();
obnoxious();

/*
let allProducts = document.querySelectorAll('td');
for (let product of allProducts) {
    product.addEventListener('mouseover', function (e) {
        product.style.backgroundColor = 'lightgreen';
    })
}
*/

// Question: Why is the row being added in the end even though I am adding it on top of the code. I had a very simple version of the code but trying to get the row added on top got me to duplicate the code and make it so long. I want to understand this better.