//
//  main.cpp
//  RoadTripCalculator
//
//  Created by Anirudh Lath on 8/24/21.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    int drivingDistanceInMiles;
    float mpg;
    float costPerGallon;
    std::cout << "How far will you travel? \n";
    std::cin >> drivingDistanceInMiles;
    std::cout << "What is your car's mileage in MPG? \n";
    std::cin >> mpg;
    std::cout << "What is the cost of gas per gallon?\n";
    std::cin >> costPerGallon;
    float gallons = drivingDistanceInMiles / mpg;
    float totalCost = gallons * costPerGallon;
    std::cout << "Your total cost of trip is: \n    $" << totalCost << std::endl;
    std::cout << "Total gallons used: \n    " << gallons << "Gallons" << std::endl;
    return 0;
}
