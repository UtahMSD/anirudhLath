//
//  main.cpp
//  MagicDates
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

    // Input
    cout << "Please enter a date in mm/dd/yyyy format:\n";
    cin >> date;

    // Logic - String manipulation and extraction (There is room for improving the versatility of the code, but for now I have just hard coded the math according to the assignment requirements.
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

    // Convert string to integers and assign a variable to check for magic date.
    bool magicDate;
    int m = stoi(mm);
    int d = stoi(dd);
    int yy = stoi(yyyy);
    int y = stoi(yyyy.substr(2));


    // Logic - Magic Date
    // Month assignments and Invalid Date Check
    if (yy < 1000 or yy > 9999) {
        cout << "\nNot a valid date! Please restart the program and try again!\n\n";
        return 1;
    }

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
        if (m * d == y) {
            cout << endl << date << " IS a magic date!" << endl << endl;
        } else {
            cout << endl << date << " is NOT a magic date!" << endl << endl;
        }
    } else if (d >= 28 and mm == "February" and y % 4 != 0) {
        cout << "\nThere can't be more than 28 days in February because " << yyyy << " is not a leap year.\n\n";
        return 1;
    } else {
        cout << "\nInvalid day in month, please try again. Program will now exit.\n\n";
        return 1;
    }

    return 0;
}
