#include <iostream>
#include <vector>
#include "HelperFunctions.hpp"
 using namespace std;

int main() {
    //Variables
    vector<int> sumList = {0,1,2,3,1,-1};
    string str = "Hello, World!";

    //Output and Logic
    assert(sum(sumList) == 6);
    assert(stringToVec(str)[0] == 'H');
    assert(reverse(sumList)[0] == -1);
    assert(reverse(sumList)[1] == 1);
    return 0;
}
