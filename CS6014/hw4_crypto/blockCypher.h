//
// Created by Anirudh Lath on 4/17/22.
//

#ifndef HW4_CRYPTO_BLOCKCYPHER_H
#define HW4_CRYPTO_BLOCKCYPHER_H

#include <cstdint>
#include <string>

void generateKey(const std::string &password, uint8_t (&key)[8]);

void createTables(uint8_t (&substTables)[8][256]);

void encrypt(const uint8_t *key, uint8_t (&substTables)[8][256], uint8_t (&plaintext_arr)[11], uint8_t n);
void decrypt(const uint8_t *key, uint8_t (&substTables)[8][256], uint8_t (&plaintext_arr)[11], uint8_t n);

void XOR(const uint8_t *key, uint8_t (&plaintext_arr)[11], uint8_t n);



#endif //HW4_CRYPTO_BLOCKCYPHER_H
