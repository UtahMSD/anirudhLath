let testNumsArray = [2,5,6,2,5,9,5];
let testStringsArray = ['g','hello', 'world', 'g', 'a'];
let people = [
    p1 = {
        'first': 'John',
        'last' : 'Appleseed',
    },
    p2 = {
        'first': 'Anirudh',
        'last' : 'Lath',
    },
    p3 = {
        'first': 'Deepak',
        'last' : 'Bagaria',
    },
    p4 = {
        'first': 'Heather',
        'last' : 'Row',
    },
    p5 = {
        'first': 'Jake',
        'last' : 'Row',
    },
    p6 = {
        'first': 'Danny',
        'last' : 'Williams',
    },
    p7 = {
        'first': 'Andy',
        'last' : 'Larrouse',
    },
];

function lessThan(a, b) {
    return a < b;
}

function greaterThan(a, b) {
    return a > b;
}

function findMinLocation(a, i, comparator) {
    let minValueIndex = i;
    for (let x = i + 1; x < a.length; x++) {
        if(comparator(a[x], a[minValueIndex])) {
            minValueIndex = x;
        }
    }
    return minValueIndex;
}



function selectionSort(a, comparator) {
    console.log(a);
    let n = a.length;
    for (let i = 0; i < n; i++) {
        let minIndex = findMinLocation(a, i, comparator);
        let temp = a[i];
        a[i] = a[minIndex];
        a[minIndex] = temp;
    }
    console.log(a);

    /*for (let i = 0; i < n-1; i++)
    {
        for (let j = i+1; j < n; j++) {
            if (a[i] > a[j] || b) {
                let temp = a[j];
                a[j] = a[i];
                a[i] = temp;
            }
        }
    }*/
}

function peopleSort(a, b) {
    if(a.last === b.last) {
        return a.first < b.first
    } else if(a.last < b.last) {
        return true;
    } else {
        return false;
    }
}

selectionSort(testNumsArray, lessThan);
selectionSort(testStringsArray, lessThan);
selectionSort(people, peopleSort);


