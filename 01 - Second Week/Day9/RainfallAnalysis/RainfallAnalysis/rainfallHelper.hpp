//
//  rainfallHelper.hpp
//  RainfallAnalysis
//
//  Created by Anirudh Lath on 9/2/21.
//

#ifndef rainfallHelper_hpp
#define rainfallHelper_hpp

#include <stdio.h>
#include <vector>
#include <string>

// Data Stuct
struct rainData {
    std::string month;
    int year;
    double rainScale;
};

// rainDatas = {month, year, rainScale}
// Cities Struct
struct cities {
    std::vector<rainData> rainDatas;
    std::string name;
};

cities readData(std::ifstream& myStream);
void writeData(std::ofstream& myStream, std::vector<cities> vectorOfCities);

#endif /* rainfallHelper_hpp */
