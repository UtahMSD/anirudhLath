//
//  rainfallHelper.cpp
//  RainfallAnalysis
//
//  Created by Anirudh Lath on 9/2/21.
//

#include "rainfallHelper.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

cities readData(ifstream& myStream){
    string cityName;
    cities city;
    rainData rainData;
    myStream >> cityName;
    city.name = cityName;
    for(int i = 0; i < 240; i++) {
        myStream >> rainData.month >> rainData.year >> rainData.rainScale;
        city.rainDatas.push_back(rainData);
    }
    myStream.close();
    return city;
}

double averageRainfall(string month, cities city){
    double average;
    double sum = 0.00;
    int count = 0;
    
    for(rainData rainDataMonth: city.rainDatas) {
        if(rainDataMonth.month == month){
            sum += rainDataMonth.rainScale;
            count ++;
        }
    }
    average = sum / count;
    return average;
}

void sortRainData(cities& city){
    for (int i = 0; i < city.rainDatas.size(); i++) {
        for (int x = 0; x < city.rainDatas.size(); x++) {
            if(city.rainDatas[i].rainScale < city.rainDatas[x].rainScale) {
                swap(city.rainDatas[i], city.rainDatas[x]);
            }
        }
    }
}

vector<double> fourWettestMonths(cities city){
    vector<double> wettestMonths;
    sortRainData(city);
    for (int i = city.rainDatas.size() - 1; i > city.rainDatas.size() - 5; i--) {
        wettestMonths.push_back(city.rainDatas[i].rainScale);
    }
    return wettestMonths;
}

vector<double> fourDriestMonths(cities city){
    vector<double> driestMonths;
    sortRainData(city);
    for (int i = 0; i < 5; i++) {
        driestMonths.push_back(city.rainDatas[i].rainScale);
    }
    return driestMonths;
}

rainData medianRain(cities city){
    sortRainData(city);
    double medianIndex;
    if(city.rainDatas.size() % 2 == 0){
        medianIndex = (city.rainDatas.size() + 1) / 2;
    } else {
        medianIndex = city.rainDatas.size() / 2;
    }
    return city.rainDatas[medianIndex];
}

void writeData(ofstream& myStream, vector<cities> vectorOfCities){
    myStream << "CS 6010 Rainfall Analysis" << endl;
    for(cities city: vectorOfCities){
        myStream << "Rainfall data for " << city.name << endl << endl << fixed << setprecision(2);
        myStream << "The average rainfall amount for January is " << averageRainfall("January", city) << " inches." << endl;
        myStream << "The average rainfall amount for February is " << averageRainfall("February", city) << " inches." << endl;
        myStream << "The average rainfall amount for March is " << averageRainfall("March", city) << " inches." << endl;
        myStream << "The average rainfall amount for April is " << averageRainfall("April", city) << " inches." << endl;
        myStream << "The average rainfall amount for May is " << averageRainfall("May", city) << " inches." << endl;
        myStream << "The average rainfall amount for June is " << averageRainfall("June", city) << " inches." << endl;
        myStream << "The average rainfall amount for July is " << averageRainfall("July", city) << " inches." << endl;
        myStream << "The average rainfall amount for August is " << averageRainfall("August", city) << " inches." << endl;
        myStream << "The average rainfall amount for September is " << averageRainfall("September", city) << " inches." << endl;
        myStream << "The average rainfall amount for October is " << averageRainfall("October", city) << " inches." << endl;
        myStream << "The average rainfall amount for November is " << averageRainfall("November", city) << " inches." << endl;
        myStream << "The average rainfall amount for December is " << averageRainfall("December", city) << " inches." << endl;
        
        // Wettest Months
        myStream << "The rain amount (in inches) of the four wettest months is: ";
        vector<double> wettestMonths = fourWettestMonths(city);
        for (double data: wettestMonths) {
            myStream << data << " ";
        }
        myStream << endl;
        
        // Driest Months
        myStream << "The rain amount (in inches) of the four driest months is: ";
        vector<double> driestMonths = fourDriestMonths(city);
        for (double data: driestMonths) {
            myStream << data << " ";
        }
        myStream << endl;
        
        //Median Month
        myStream << "The median month is:\n";
        rainData median = medianRain(city);
        myStream << median.month << " " << median.year << " " << median.rainScale << endl << endl;
        
        
    }
    myStream.close();
}
