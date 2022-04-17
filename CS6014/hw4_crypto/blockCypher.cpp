//
// Created by Anirudh Lath on 4/17/22.
//

#include "blockCypher.h"

using namespace std;

void encrypt(const uint8_t *key, uint8_t (&substTables)[8][256], uint8_t (&plaintext_arr)[11], uint8_t n) {
    for (int j = 0; j < 16; ++j) {
        XOR(key, plaintext_arr, n); // XOR key

        for (int i = 0; i < n; ++i) { // substitute
            plaintext_arr[i] = substTables[i % 8][plaintext_arr[i]];
        }


        uint8_t msbFirstByte = plaintext_arr[0] >> 7;
        for (int i = 0; i < n - 1; ++i) {
            plaintext_arr[i] = plaintext_arr[i] << 1 | plaintext_arr[i + 1] >> 7;
        }
        plaintext_arr[n - 1] = (plaintext_arr[n - 1] << 1) | msbFirstByte;


    }
}

void XOR(const uint8_t *key, uint8_t (&plaintext_arr)[11], uint8_t n) {
    for (int i = 0; i < n; ++i) {
        plaintext_arr[i] = plaintext_arr[i] ^ key[i % 8];
    }
}

void decrypt(const uint8_t *key, uint8_t (&substTables)[8][256], uint8_t (&plaintext_arr)[11], uint8_t n) {
    for (int j = 0; j < 16; ++j) {

        uint8_t lsbCurrentByte = plaintext_arr[n - 1] << 7;
        for (int i = 0; i < n; ++i) {
            uint8_t lsbNextByte = plaintext_arr[i] << 7;
            plaintext_arr[i] = (plaintext_arr[i] >> 1) | lsbCurrentByte;
            lsbCurrentByte = lsbNextByte;
        }


        for (int i = n - 1; i >= 0; --i) { // undo substitution
            for (int k = 0; k < 256; ++k) {
                if (plaintext_arr[i] == substTables[i % 8][k]) {
                    plaintext_arr[i] = k;
                    break;
                }
            }
        }

        XOR(key, plaintext_arr, n); // XOR key
    }
}

void createTables(uint8_t (&substTables)[8][256]) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 256; ++j) {
            substTables[i][j] = j;
        }
        random_shuffle(begin(substTables[i]), end(substTables[i]));
    }
}

void generateKey(const string &password, uint8_t key[8]) {

    for (int i = 0; i < password.length(); ++i) {
        key[i % 8] = key[i % 8] ^ password[i];
    }
}

