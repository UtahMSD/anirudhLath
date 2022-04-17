//
// Created by Anirudh Lath on 4/17/22.
//

#ifndef HW4_CRYPTO_RC4CYPHER_H
#define HW4_CRYPTO_RC4CYPHER_H

#include <cstdint>
#include <string>
#include <iostream>

class RC4 {
    uint8_t arr[256];
    uint8_t key[8];
    std::string plainText;
    std::string cipherText;
public:
    RC4(std::string &password);
    std::string encrypt(std::string &message);
    std::string decrypt(uint8_t key[8]);
    std::string decrypt(std::string encryptedText);
    void printCipherText() {
        std::cout << cipherText << std::endl;
    }
    uint8_t* getKey() {
        return this->key;
    }

    void initTable(const uint8_t *key);
};

#endif //HW4_CRYPTO_RC4CYPHER_H
