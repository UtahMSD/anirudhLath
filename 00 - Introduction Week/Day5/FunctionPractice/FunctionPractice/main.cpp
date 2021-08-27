//
//  main.cpp
//  FunctionPractice
//
//  Created by Anirudh Lath on 8/27/21.
//

#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

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
    double hypotenuse = sqrt(pow(firstSide, 2) + pow(secondSide, 2));
    
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
    std::time_t result = std::time(nullptr);
        std::cout << std::asctime(std::localtime(&result))
                  << result << " seconds since the Epoch\n";
    
    
    return 0;
}
