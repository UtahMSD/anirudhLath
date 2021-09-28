//
//  main.cpp
//  NumberRepresentations
//
//  Created by Anirudh Lath on 9/8/21.
//

#include <iostream>
#include <cstdint>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

bool approxEquals(double a, double b, double tolerance) {
//    double sum = a + b;
//    cout << sum - (a + b) << endl;
    if(abs(a - b) < tolerance) {
//        cout << abs(sum - (a + b)) << endl;
        return true;
    }
    return false;
}

void readData(ifstream &infile, int &asciiCount, int &unicodeCount) {
    char c;
    while( infile >> c ) {
        cout << c << endl;
        if(c < 0) {
            unicodeCount++;
        }
        if( c >= 0){
            asciiCount++;
        }
    }
    cout << endl;
    cout << "ASCII Count: " << asciiCount << endl;
    cout << "Unicode Count: " << unicodeCount << endl;
    cout << endl;
}

int main(int argc, const char * argv[]) {
    int a = 1;
    char b = 'a';
    bool c = true;
    double d = 1.212321313;
    float e = 1.2;
    string f = "TEST";
    
    cout << "Integer: " << sizeof(a) << " bytes" << endl;
    cout << "Character: " << sizeof(b) << " bytes" << endl;
    cout << "Boolean: " << sizeof(c) << " bytes" << endl;
    cout << "Double: " << sizeof(d) << " bytes" << endl;
    cout << "Float: " << sizeof(e) << " bytes" << endl;
    cout << "String: " << sizeof(f) << " bytes" << endl << endl;
    
    u_int8_t int8min = 0xFF;
    u_int8_t int8max = 0x00;
    u_int16_t int16min = 0xFFFF;
    u_int16_t int16max = 0x0000;
    u_int32_t int32min = 0xFFFFFFFF;
    u_int32_t int32max = 0x00000000;
    int8_t int8tmin = 0x80;
    int8_t int8tmax = 0x7F;
    int16_t int16tmin = 0x8000;
    int16_t int16tmax = 0x7FFF;
    int32_t int32tmin = 0x80000000;
    int32_t int32tmax = 0x7FFFFFFF;
    
    cout << "u_int8_t:" << endl;
    cout << "Value Max: " << +int8min << endl;
    cout << "Value Min: " << +int8max << endl;
    cout << "Size in bytes: " << sizeof(int8min) << endl << endl;
    
    cout << "u_int16_t:" << endl;
    cout << "Value Max: " << +int16min << endl;
    cout << "Value Min: " << +int16max << endl;
    cout << "Size in bytes: " << sizeof(int16min) << endl << endl;
    
    cout << "u_int32_t:" << endl;
    cout << "Value Max: " << +int32min << endl;
    cout << "Value Min: " << +int32max << endl;
    cout << "Size in bytes: " << sizeof(int32min) << endl << endl;
    
    cout << "int8_t:" << endl;
    cout << "Value Max: " << +int8tmin << endl;
    cout << "Value Min: " << +int8tmax << endl;
    cout << "Size in bytes: " << sizeof(int8tmin) << endl << endl;
    
    cout << "int16_t:" << endl;
    cout << "Value Max: " << +int16tmin << endl;
    cout << "Value Min: " << +int16tmax << endl;
    cout << "Size in bytes: " << sizeof(int16tmin) << endl << endl;
    
    cout << "int32_t:" << endl;
    cout << "Value Max: " << +int32tmin << endl;
    cout << "Value Min: " << +int32tmax << endl;
    cout << "Size in bytes: " << sizeof(int32tmin) << endl << endl;
    
    double x = 0.1;
    double y = 0.2;
    float i = 0.1;
    float j = 0.2;
    
    //assert(x + y == 0.3); // Fails because x and y are not exactly 0.1 and 0.2 respectively.
    //assert(i + j == 0.3); // Fails because i and j are not exactly 0.1 and 0.2 respectively. I remember from the class that float should work but in my case it is failing.
    cout << setprecision(18);
    cout << "Double x:" << x << endl;
    cout << "Double y:" << y << endl;
    cout << " x + y = " << x + y << endl << endl;
    cout << "Float i: " << i << endl;
    cout << "Float j: " << j << endl;
    cout << " i + j = " << i + j << endl << endl;
    
    assert(approxEquals(x, y, 0.1000001) == true);
    
    
    ifstream infile("utf.txt");
    int asciiCount = 0;
    int unicodeCount = 0;
    
    readData(infile, asciiCount, unicodeCount);
    
    return 0;
}

