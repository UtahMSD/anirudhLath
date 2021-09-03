//
//  main.cpp
//  RainfallAnalysis
//
//  Created by Anirudh Lath on 9/2/21.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "rainfallHelper.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    // Variable assignments
    string filename1 = "Day9_MaconRainfall.txt";
    ifstream file1(filename1);
    //string filename2 = "Day9_AtlantaRainfall.txt";
    //ifstream file2(filename2);
    cities city1;
    //cities city2;
    string writeFilename = "rainfall_results.txt";
    ofstream writeFile(writeFilename);
    vector<cities> vectorOfCities;
    
    // Testing
    if(file1.fail()) {
        cout << "Failed to open file: " << filename1 << endl;
        exit(1);
    }
//    if(file2.fail()) {
//        cout << "Failed to open file: " << filename2 << endl;
//        exit(1);
//    }
    
    // Read Files
    city1 = readData(file1);
    //city2 = readData(file2);
    
    // Append a city to a vector
    vectorOfCities.push_back(city1);
    //vectorOfCities.push_back(city2);
    
    // Write Files
    writeData(writeFile, vectorOfCities);
    
    
    return 0;
}
