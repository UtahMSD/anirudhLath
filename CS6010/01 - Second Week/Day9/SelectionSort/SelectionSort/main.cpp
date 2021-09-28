//
//  main.cpp
//  SelectionSort
//
//  Created by Anirudh Lath on 9/2/21.
//

#include <iostream>
#include <vector>
using namespace std;

int findIndexOsSmallest( const vector<float> & numbers, int currentIndex) {
    int smallest = numbers[currentIndex];
    for (int i = currentIndex + 1; i < numbers.size(); i++) {
        if (numbers[i] < smallest) {
            smallest = numbers[i];
            currentIndex = i;
        }
    }
    return currentIndex;
}

int main(int argc, const char * argv[]) {
    // Variables
    vector<float> test = {-10, 1, 2, -10, 100, 99};
    
    for (int i = 0; i < test.size() ; i++) {
        int smallestIndex = findIndexOsSmallest(test, i);
        swap(test[i], test[smallestIndex]);
        cout << test[i] << "   ";
    }

    return 0;
}
