#include <iostream>
#include <string>
#include <cstdint>
#include <random>
#include <algorithm>
#include <bitset>
#include "blockCypher.h"
#include "rc4Cypher.h"


void bitShiftAttack();

using namespace std;

bool blockCypherTest() {
    uint8_t key[8];
    string password = "helloworld";

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


    cout << "\n";

    decrypt(key, substTables, plaintext_arr, n);


    for (int i = 0; i < 11; ++i) {
        if (plaintext_arr[i] != message[i]) {
            return false;
        }
    }
    return true;
}

bool rc4Test() {
    string password = "hello";
//    string password2= "helloworld";
    uint8_t key1[8] = {1,2,3,4,5,6,7,8};
    RC4 *rc4 = new RC4(password);
    string message = "hello this is rudy";
    string cipher1 = rc4->encrypt(message);
    generateKey(password, key1);
    string decrypted = rc4->decrypt(rc4->getKey());
    for (int i = 0; i < message.length(); ++i) {
        if (message[i] != decrypted[i]) {
            return false;
        }
    }

    bool check1 = false; // Verify that decrypting a message with a different key than the encryption key does not reveal the plaintext.
    decrypted = rc4->decrypt(key1);
    for (int i = 0; i < message.length(); ++i) {
        if (message[i] != decrypted[i]) {
            check1 = true;
        }
    }
    if (!check1) {
        cout << "Cannot verify that decrypting a message with a different key than the encryption key does not reveal"
                " the plaintext.";
        return false;
    }

    // Verify that encrypting 2 messages using the same keystream is insecure.
    string message2 = "hello world";
    string cipher2 = rc4->encrypt(message2);
    int n = 0;
    if(cipher1.length() > cipher2.length()) {
        n = cipher2.length();
    } else {
        n = cipher1.length();
    }
    cout << "Cipher 1:  " << cipher1 << endl;
    cout << "Cipher 2:  " << cipher2 << endl;
    cout << "C1 xor C2: ";

    for (int i = 0; i < n; ++i) {
        cout << (cipher1[i] ^ cipher2[i]);
    }
    cout << "\n";

    bitShiftAttack();


    return true;
}

void bitShiftAttack() {
    string one = "Salary";
    string two = "Your salary is $1000";
    RC4 salary = RC4(one);
    string salaryEncrypted = salary.encrypt(two);
    string newSalaryEncrypted = "";
    for(int i = 0; i < salaryEncrypted.length(); i++){
        if (i == 17 || i == 18 || i == 19){
            newSalaryEncrypted += salaryEncrypted.at(i) ^ 0x09; // Since the plaintext has '0' we can xor the number
            // we want.
        }
        else if (i == 16 ) {
            newSalaryEncrypted += salaryEncrypted.at(i) ^ 0x08; // Since the plaintext has '1' we subtract that with
            // the desired number and xor that in.
        }
        else {
            newSalaryEncrypted += salaryEncrypted[i];
        }
    }
    string decryptedSalary = salary.decrypt(newSalaryEncrypted);
    cout << "New Salary Decrypted: "<< decryptedSalary << endl;
}

int main() {

    if (!blockCypherTest()) {
        cout << "Block cypher failed.\n";
        return 1;
    } else {
        cout << "Block cypher test passed.\n";
    }

    if (!rc4Test()) {
        cout << "RC4 cypher failed.\n";
        return 1;
    } else {
        cout << "RC4 test passed.\n";
    }


    return 0;
}

