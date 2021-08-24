//
//  main.cpp
//  VolumeConvert
//
//  Created by Anirudh Lath on 8/24/21.
//

#include <iostream>

int main(int argc, const char * argv[]) {

    //Variable assignment
    float ounces;
    
    //Input
    std::cout << "Please enter the number of ounces you would like to convert:\n";
    std::cin >> ounces;
    
    //Logic
    float cups = ounces/8;
    float pints = ounces/16;
    float gallons = ounces/128;
    float liters = 0.0296 * ounces;
    float cubicInches = 1.8 * ounces;
    
    //Output
    std::cout << "The converted volume " << ounces << " ounces is as follows:\n";
    std::cout << cups << " cups\n";
    std::cout << pints << " pints\n";
    std::cout << gallons << " gallons\n";
    std::cout << liters << " liters\n";
    std::cout << cubicInches << " cubic inches\n";

    return 0;
}
