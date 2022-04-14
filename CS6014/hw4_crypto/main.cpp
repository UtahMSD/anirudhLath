#include <iostream>
#include <string>
#include <cstdint>
#include <random>


using namespace std;

void generateKey(const string &password, uint8_t key[8]);

void createTables(uint8_t *substTables[256]);

void encrypt(const uint8_t *key, uint8_t *substTables[256], uint8_t plaintext_arr[], int n);

void swap (uint8_t *a, uint8_t *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    uint8_t key[8];
    string password = "";
    std::cout << "Please enter a password: ";
    cin >> password;

    generateKey(password, key);


    uint8_t *substTables[256];

    createTables(substTables);

    string message = "";
    std::cout << "Please enter a message: ";
    cin >> message;

    uint8_t plaintext_arr[message.length()];

    for (int i = 0; i < message.length(); ++i) {
        plaintext_arr[i] = message[i];
    }

    //
    int n = message.length();
    encrypt(key, substTables, plaintext_arr, n);


    return 0;
}

void encrypt(const uint8_t *key, uint8_t *substTables[256], uint8_t plaintext_arr[], int n) {
    for (int i = 0; i < 16; ++i) {
        for (int i = 0; i < n; ++i) {
            plaintext_arr[i] = plaintext_arr[i] xor key[i % 8];
        }

        for (int i = 0; i < n; ++i) {
            auto index = substTables[i];
            plaintext_arr[i] = index[plaintext_arr[i]];

        }

        for (int i = 0; i < n; ++i) {
            plaintext_arr[i] = plaintext_arr[i] << 1;
            uint8_t msb = 1 << 7;
            if (i < n - 1) {
                uint8_t num = plaintext_arr[i + 1];
                if ((num & msb) == 1) {
                    plaintext_arr[i] = plaintext_arr[i] & 0xFE | 1;
                }
            }
            else {
                uint8_t num = plaintext_arr[0];
                if ((num & msb) == 1) {
                    plaintext_arr[i] = plaintext_arr[i] & 0xFE | 1;
                }
            }
        }
    }
}

void createTables(uint8_t *substTables[256]) {
    uint8_t substTable[256];
    for (int i = 0; i < 256; ++i) {
        substTable[i] = (uint8_t) i;
    }
    cout << endl << '[' << endl;
    for (int i = 0; i < 8; ++i) {
        cout << "   [";
        for (int j = 255; j > 0; j--) {
            int random = rand() % (i + 1);
            swap(&substTable[j], &substTable[random]);
            uint8_t num = substTable[j];
            swap(&substTable[i][j], num);
            cout << substTables[i][j] << ", ";
            if( j % 10 == 0) {
                cout << "\n";
            }
        }
        cout << "],\n";
    }
    cout << ']' << endl;
}

void generateKey(const string &password, uint8_t key[8]) {

    for (int i = 0; i < password.length(); ++i) {
        key[i % 8] = key[i % 8] xor password[i];
        cout << key[i];
    }
}
