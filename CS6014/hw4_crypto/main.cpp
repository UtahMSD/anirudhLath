#include <iostream>
#include <string>
#include <cstdint>
#include <random>
#include <algorithm>
#include <bitset>
#include "blockCypher.h"


using namespace std;

void swap (uint8_t *a, uint8_t *b)
{
    uint8_t temp = *a;
    *a = *b;
    *b = temp;
}

bool blockCypherTest() {
    uint8_t key[8];
    string password = "";
    std::cout << "Please enter a password: ";
    cin >> password;

    generateKey(password, key);


    uint8_t substTables[8][256];

    createTables(substTables);

    string message = "hello world";

    uint8_t n = 11;
    uint8_t plaintext_arr[11];

    for (uint8_t i = 0; i < 11; ++i) {
        plaintext_arr[i] = message[i];
    }


    encrypt(key, substTables, plaintext_arr, n);

    copy(begin(plaintext_arr), end(plaintext_arr), ostream_iterator<uint8_t>(cout, ", "));

    cout << "\n";

    decrypt(key, substTables, plaintext_arr, n);

//    for (int i = 0; i < 11; ++i) {
//        plaintext_arr[i] = message[i];
//    }
//
    copy(begin(plaintext_arr), end(plaintext_arr), ostream_iterator<uint8_t>(cout, ", "));

    for (int i = 0; i < 11; ++i) {
        if (plaintext_arr[i] != message[i]) {
            return false;
        }
    }
    return true;
}

int main() {

    if (!blockCypherTest()) {
        cout << "Block cypher failed.\n";
        return 1;
    }

    return 0;
}

