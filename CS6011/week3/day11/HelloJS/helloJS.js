document.writeln("<p>hello world</p>"); // Used to actually insert text to the document.
console.log("hello world"); // Used to output data to the console.

let x = [
    "hello",
    true,
    25,
    {
        "key": "test",
        "value": "hello world",
    }
];

for(let i of x) { console.log(i);}

x[1] = false;

for(let i of x) { console.log(i);}

// I didn't see anything weird in particular.


function test(x) {
    for(let i of x) { console.log(i);}
}

let testFunction = function(x) {
    for(let i of x) { console.log(i);}
}

test(x);
testFunction(x);

// I honestly prefer the C++ style. Just to keep it simple.
// I think the difference here is that the 'let' method
// allows us to reassign the function to a different data type.

test([2,3,4,5]);
testFunction([2,3,4,5]);

test([2.1,3.0,4.0,5.0]);
testFunction([2.1,3.0,4.0,5.0]);

test(["h",3,4.0,true]);
testFunction(["h",3,4.0,true]);

// I noticed that the functions with floating point number automatically
// show up as integers, if it has .0 in the end.