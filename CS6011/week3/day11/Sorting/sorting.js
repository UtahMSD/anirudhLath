let testNumsArray = [2,5,6,2,5,9,5];
let testStringsArray = ['g','hello', 'world', 'g', 'a'];
let people = [
    { 
        'first': 'John',
        'last' : 'Appleseed',
    },
    { 
        'first': 'Anirudh',
        'last' : 'Lath',
    },
    { 
        'first': 'Deepak',
        'last' : 'Bagaria',
    },
    { 
        'first': 'Heather',
        'last' : 'Row',
    },
    { 
        'first': 'Jake',
        'last' : 'Harlow',
    },
    { 
        'first': 'Danny',
        'last' : 'Williams',
    },
    { 
        'first': 'Andy',
        'last' : 'Larrouse',
    },
];
function findMinLocation(a) {
    let minValueIndex = 0;
    for (let i = 1; i < a.length; i++) {
        if(a[i] < a[minValueIndex]) {
            minValueIndex = i;
        }
    }
    return minValueIndex;
}

function lessThan(a, b) {
    return a < b;
}

function selectionSort(a, b) { 
    let n = a.length;
    console.log(a);
    for (let i = 0; i < n-1; i++)
    {
        for (let j = i+1; j < n; j++) {
            if (a[i] > a[j] || b) {
                let temp = a[j];
                a[j] = a[i];
                a[i] = temp;
            }
        }
    }
    console.log(a);
}

selectionSort(testNumsArray);
selectionSort(testStringsArray);
selectionSort(testNumsArray, lessThan(2,3));
selectionSort(testNumsArray, lessThan(2,3));
selectionSort(people, lessThan(people.last,people.first));
