//
//  main.cpp
//  IfStatementPractice
//
//  Created by Anirudh Lath on 8/25/21.
//

#include <iostream>

int main(int argc, const char * argv[]) {

    /// Part 1:
    // Variables
    int userAge;
    int votingAge = 21;
    int senateAge = 25;

    // Ask user for their age
    std::cout << "Kindly enter your age below:\n";
    std::cin >> userAge;

    // Logic and Output
    if (userAge >= votingAge) {
        std::cout << "You are old enough to vote!" << std::endl;
    } else {
        std::cout << "You are not old enough to vote!" << std::endl;
    }
    if (userAge >= senateAge) {
        std::cout << "You are old enough to run for the Senate!" << std::endl;
    } else {
        std::cout << "You are not old enough to run for the Senate!" << std::endl;
    }

    if (userAge >= 80) {
        std::cout << "You are a part of the greatest generation!" << std::endl;
    } else if (userAge >= 60) {
        std::cout << "You are a part of the baby boomer!" << std::endl;
    } else if (userAge >= 40) {
        std::cout << "You are a part of the generation!" << std::endl;
    } else if (userAge >= 20) {
        std::cout << "You are a part of the millennial!" << std::endl;
    } else {
        std::cout << "You are a part of the iKid!" << std::endl;
    }

    /// Part 2
    // Variables
    char weekday;
    char holiday;
    char youngChildren;
    bool isWeekday;
    bool isHoliday;
    bool isYoungChildren;

    // Ask user for their age
    std::cout << "Kindly enter Y or N based on if it is a weekday or not:" << std::endl;
    std::cin >> weekday;

    std::cout << "Kindly enter Y or N based on if it is a holiday or not:" << std::endl;
    std::cin >> holiday;

    std::cout << "Kindly enter Y or N based on if you have children or not:" << std::endl;
    std::cin >> youngChildren;

    // Logic and Output
    if (weekday == 'Y' or weekday == 'y') {
        isWeekday = true;
    } else if (weekday == 'N' or weekday == 'n'){
        isWeekday = false;
    } else {
        std::cout << "Invalid Response! Restart the program!" << std::endl;
        return 1;
    }

    if (holiday == 'Y' or holiday == 'y') {
        isHoliday = true;
    } else if (holiday == 'N' or holiday == 'n'){
        isHoliday = false;
    } else {
        std::cout << "Invalid Response! Restart the program!" << std::endl;
        return 1;
    }

    if (youngChildren == 'Y' or youngChildren == 'y') {
        isYoungChildren = true;
    } else if (youngChildren == 'N' or youngChildren == 'n'){
        isYoungChildren = false;
    } else {
        std::cout << "Invalid Response! Restart the program!" << std::endl;
        return 1;
    }

    if (isYoungChildren) {
        std::cout << "You cannot sleep in today :(" << std::endl;
    } else if (isHoliday or not isWeekday) {
        std::cout << "You can sleep in today :)" << std::endl;
    } else {
        std::cout << "You cannot sleep in today :)" << std::endl;
    }


    return 0;
}
