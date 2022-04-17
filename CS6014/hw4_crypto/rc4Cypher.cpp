//
// Created by Anirudh Lath on 4/17/22.
//

#include "rc4Cypher.h"
#include "blockCypher.h"
#include <stdio.h>

using namespace std;

RC4::RC4(std::string &password) {
    generateKey(password, key);
    initTable(key);
}

void RC4::initTable(const uint8_t *key) {
    for (int i = 0; i < 256; ++i) {
        arr[i] = i;
    }
    int offset = 0;
    for (int i = 0; i < 256; ++i) {
        offset = (offset + arr[i] + key[i % 8]) % 256;
        swap(arr[i], arr[offset]);
    }
}

string RC4::encrypt(std::string &message) {
    plainText = message;
    cipherText = "";
    int i = 0;
    int j = 0;
    for (int k = 0; k < message.length(); ++k) {
        i = (i + 1) % 256;
        j = (j + 1) % 256;
        swap(arr[i], arr[j]);
        cipherText.push_back(arr[(arr[i] + arr[j]) % 256] ^ message[k]);
    }
    return cipherText;
}

string RC4::decrypt(uint8_t key[8]) {
    initTable(key);
    string decrypted = "";
    int i = 0;
    int j = 0;
    for (int k = 0; k < cipherText.length(); ++k) {
        i = (i + 1) % 256;
        j = (j + 1) % 256;
        swap(arr[i], arr[j]);
        decrypted.push_back(arr[(arr[i] + arr[j]) % 256] ^ cipherText[k]);
    }
    return decrypted;
}

std::string RC4::decrypt(std::string encryptedText) {
    initTable(key);
    cipherText = "";
    plainText = "";
    string decrypted = "";
    int i = 0;
    int j = 0;
    for (int k = 0; k < encryptedText.length(); ++k) {
        i = (i + 1) % 256;
        j = (j + 1) % 256;
        swap(arr[i], arr[j]);
        decrypted.push_back(arr[(arr[i] + arr[j]) % 256] ^ encryptedText[k]);
    }
    return decrypted;
}
