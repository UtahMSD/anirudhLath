//
//  main.cpp
//  Average
//
//  Created by Anirudh Lath  & Andrew Kellett on 8/24/21.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    //Variable Assignments
    int a;
    int b;
    int c;
    int d;
    int e;

    //Input
    std::cout << "Enter the 5 assignment scores individually:\n";
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;
    std::cin >> d;
    std::cin >> e;

    //Average
    float average =  (a + b + c + d + e) / 5.0;

    //Output
    std::cout << "Your average score is: " << average << std::endl;

    return 0;
}
