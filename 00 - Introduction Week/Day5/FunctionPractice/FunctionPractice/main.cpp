//
//  main.cpp
//  FunctionPractice
//
//  Created by Anirudh Lath on 8/27/21.
//
// Part 2: Question 1
// It is best to keep input in main() because that way the child function doesn't take control or cause halts or any other issues in the main function. It is just not a healthy way to do it. It will break the flow of the program too.
// Part 2: Question 2
// It would be difficult because a function should only have one return value ideally. The program can get confused about which variable to assign to in main().


#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

double calculateHypotenuse(double firstSide, double secondSide) {
    double hypotenuse = sqrt(pow(firstSide, 2) + pow(secondSide, 2));
    return hypotenuse;
}

bool isCapitalized(string str) {
    return isupper(str[0]);
}

string boolToString(bool boolean) {
    if (boolean) {
        return "True";
    } else {
        return "False";
    }
}

bool isPrime(int num) {
    
    int count = 0;
    
    for (int i = 2; i <= num; i++) {
        if (num % i == 0) {
            count += 1;
        }
    }
    if (count == 1) {
        return true;
    } else {
        return false;
    }
}

int main(int argc, const char * argv[]) {
    
    /// A
    // Variables
    double firstSide;
    double secondSide;
    
    //Input
    cout << "Hello, Please enter the length of a right angle side of your triangle:\n";
    cin >> firstSide;
    cout << endl;
    
    cout << "Hello, Please enter the length of the other right angle side of your triangle:\n";
    cin >> secondSide;
    cout << endl;
    
    // Logic
//    double hypotenuse = sqrt(pow(firstSide, 2) + pow(secondSide, 2));
    double hypotenuse = calculateHypotenuse(firstSide, secondSide);
    
    // Output
    cout << "The length of the hypotenuse is:\n" << hypotenuse << endl << endl;
    
    
    /// B
    // Variables
    double speed = 0.0;
    double angle = 0.0;
    
    //Input
    cout << "Hello, Please enter your speed:\n";
    cin >> speed;
    cout << endl;
    
    cout << "Hello, Please enter the angle you are heading towards:\n";
    cin >> angle;
    cout << endl;
    
    // Logic
    double x = speed * cos(angle);
    double y = speed * sin(angle);
    
    // Output
    cout << "Your x velocity is:\n" << x << endl << endl;
    cout << "Your y velocity is:\n" << y << endl << endl;
    
    
    /// C
    // Code works as expected!
    std::time_t result = std::time(nullptr);
        std::cout << std::asctime(std::localtime(&result))
                  << result << " seconds since the Epoch\n";
    
    /// Part 2: isCapitalized and boolToString
    // Variables
    string str;
    
    //Input
    cout << "\nPlease enter a word:\n";
    cin >> str;
    cout << endl;
    
    // Logic
    cout << boolToString(isCapitalized(str)) << endl << endl; //boolToString used here.
    
    
    /// Part 2: isPrime
    // Variables
    int prime;
    
    //Input
    cout << "Please enter a number:\n";
    cin >> prime;
    cout << endl;
    
    // Logic
    cout << boolToString(isPrime(prime)) << endl << endl; //boolToString used here.
    
    
    return 0;
}
