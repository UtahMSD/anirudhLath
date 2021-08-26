//
//  main.cpp
//  DateFormats
//
//  Created by Anirudh Lath on 8/26/21.
//

#include <iostream>

using namespace std;

int main(int argc, const char * argv[]) {
    // Variables
    string date = "";
    string mmdd;
    string mm;
    string dd;
    string yyyy;
    int pos1;
    int pos2;
    int count = 0;

    // Input
    cout << "Please enter a date in mm/dd/yyyy format:\n";
    cin >> date;

    // Logic
    pos1 = date.find('/') + 1;
    pos2 = date.find('/', 3) + 1;
    yyyy = date.substr(pos2);
    if (date.size() == 10) {
        dd = date.substr(pos1, (pos2 - 4));
    } else if (date.size() == 9 and pos2 > 4 and pos1 >= 3){
        dd = date.substr(pos1, (pos2 - 4));
    } else {
        dd = date.substr(pos1, (pos2 - 3));
    }
    mm = date.substr(0,(pos1 - 1));

    // Month assignments and Invalid Month Check
    if (mm == "12") {
        mm = "December";
    } else if (mm == "1" or mm == "01"){
        mm = "January";
    } else if (mm == "2" or mm == "02") {
        mm = "February";
    } else if (mm == "3" or mm == "03") {
        mm = "March";
    } else if (mm == "4" or mm == "04") {
        mm = "April";
    } else if (mm == "5" or mm == "05") {
        mm = "May";
    } else if (mm == "6" or mm == "06") {
        mm = "June";
    } else if (mm == "7" or mm == "07") {
        mm = "July";
    } else if (mm == "8" or mm == "08") {
        mm = "August";
    } else if (mm == "9" or mm == "09") {
        mm = "September";
    } else if (mm == "10") {
        mm = "October";
    } else if (mm == "11") {
        mm = "November";
    } else {
        cout << "Not a valid date! Please restart the program and try again!\n";
        return 1;
    }
    
    // Convert day and year to int for error handling
    int d = stoi(dd);
    int y = stoi(yyyy);

    // Invalid Day Check
    if ((d <= 31 and mm == "January")
    or (d <= 28 and mm == "February")
    or (d <= 29 and mm == "February" and y % 4 == 0)
    or (d <= 31 and mm == "March")
    or (d <= 30 and mm == "April")
    or (d <= 31 and mm == "May")
    or (d <= 30 and mm == "June")
    or (d <= 31 and mm == "July")
    or (d <= 31 and mm == "August")
    or (d <= 30 and mm == "September")
    or (d <= 31 and mm == "October")
    or (d <= 30 and mm == "November")
    or (d <= 31 and mm == "January")) {
        cout << endl << mm << ' ' << dd << ", " << yyyy << endl << endl;
    } else if (d >= 28 and mm == "February" and y % 4 != 0) {
        cout << "\nThere can't be more than 28 days in February because " << yyyy << " is not a leap year.\n\n";
        return 1;
    }
    else {
        cout << "\nInvalid day in month, please try again. Program will now exit.\n\n";
        return 1;
    }


    

    return 0;
}
