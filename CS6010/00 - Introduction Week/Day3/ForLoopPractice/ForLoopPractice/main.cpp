//
//  main.cpp
//  ForLoopPractice
//
//  Created by Anirudh Lath on 8/25/21.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    // For Loop for 1 - 10
    for (int i = 1; i <= 10; ++i) { //For loop is better because of readability and conciseness in code.
        std::cout << i << "    ";
    }
    std::cout << std::endl;

    // While Loop for 1 - 10
    int i = 1;
    while (i <= 10) {
        std::cout << i << "    ";
        ++i;
    }
    std::cout << std::endl;
    std::cout << std::endl;

    // Print numbers between x and y
    int x;
    int y;

    std::cout << "Enter a number:\n";
    std::cin >> x;
    std::cout << "Enter a number:\n";
    std::cin >> y;

    if (x <= y) {
        while (x <= y) {
            std::cout << x << "    ";
            ++x;
        }
    }
    else {
        while (x >= y) {
            std::cout << x << "    ";
            --x;
        }
    }
    std::cout << std::endl;
    std::cout << std::endl;

    // Odd number through loop and if statement, THIS IS BETTER AND MORE VERSATILE!
    for (int j = 1; j <= 20 ; ++j) {
        if (j % 2 != 0) {
            std::cout << j << "    ";
        }
    }
    std::cout << std::endl;

    // Odd number through loop only
    for (int a = 1; a <= 20 ; a += 2) {
        std::cout << a << "    ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    // Add numbers until 0
    int s;
    int sum = 0;
    while (s >= 0) {
        std::cout << "Enter a positive number to add:\n";
        std::cin >> s;
        sum += s;
    }
    std::cout << "Sum: " << (sum + (s *= -1)) << std::endl;
    std::cout << std::endl;

    // Multiplication Table from 1 to 5
    for (int j = 1; j <= 5; ++j) {
        std::cout << j << "x* = ";
        for (int k = 1; k <= 5 ; ++k) {
            std::cout << k * j << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;


    return 0;
}
