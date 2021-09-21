//
//  main.cpp
//  ladderDiagram
//
//  Created by Anirudh Lath on 9/19/21.
//

#include <iostream>

using namespace std;

int main(int argc, const char * argv[]) {
    
    int data[] = { 9, 3, 4, 2, 5, -1, 6 };
    int count = 0;
    data[5] = 2;
    int results[5] = { 0, 0, 0, 0, 0 };
    results[count] = -1;
    int i = 1;
    while (i < 8) {
        int n1 = data[i];
        int n2 = data[i + 1];
        if (n1 < n2) {
            data[i] = n2;
            data[i + 1] = n1;
            count = count + 1;
        }
        else if (n1 == n2) {
            printf("ERROR!");
            cout<< i << endl;
            return 1;
        }
        else {
            results[i] = n2;
        }
        i = i + 1;
    }
    printf("Done processing data.");
    return 0;
}
