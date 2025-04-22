#include <iostream>
#include <bitset>

using namespace std;

const int IP[8] = {2, 6, 3, 1, 4, 8, 5, 7};
const int IP_INV[8] = {4, 1, 3, 5, 7, 2, 8, 6};
const int P4[4] = {2, 4, 3, 1};
const int EP[8] = {4, 1, 2, 3, 2, 3, 4, 1};
const int P10[10] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
const int P8[8] = {6, 3, 7, 4, 8, 5, 10, 9};
const int S1[4][4] = {{1, 0, 3, 2}, {3, 2, 1, 0}, {0, 2, 1, 3}, {3, 1, 0, 2}};
const int S2[4][4] = {{0, 1, 2, 3}, {2, 0, 1, 3}, {3, 0, 1, 0}, {2, 1, 0, 3}};

string permute(string input, const int* table, int n) {
    string output = "";
    for (int i = 0; i < n; i++) {
        output += input[table[i] - 1];
    }
    return output;
}

string left_shift(string key, int shifts) {
    return key.substr(shifts) + key.substr(0, shifts);
}

string xor_operation(string a, string b) {
    string result = "";
    for (size_t i = 0; i < a.size(); i++) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

string s_box(string input, const int s_box[4][4]) {
    int row = (input[0] - '0') * 2 + (input[3] - '0');
    int col = (input[1] - '0') * 2 + (input[2] - '0');
    return bitset<2>(s_box[row][col]).to_string();
}

string f_function(string right, string subkey) {
    string expanded = permute(right, EP, 8);
    string xored = xor_operation(expanded, subkey);
    string left = s_box(xored.substr(0, 4), S1);
    string right_s = s_box(xored.substr(4, 4), S2);
    return permute(left + right_s, P4, 4);
}

void generate_keys(string key, string& k1, string& k2) {
    key = permute(key, P10, 10);
    string left = key.substr(0, 5);
    string right = key.substr(5, 5);
    left = left_shift(left, 1);
    right = left_shift(right, 1);
    k1 = permute(left + right, P8, 8);
    left = left_shift(left, 2);
    right = left_shift(right, 2);
    k2 = permute(left + right, P8, 8);
}

string encrypt(string plaintext, string key) {
    string k1, k2;
    generate_keys(key, k1, k2);
    plaintext = permute(plaintext, IP, 8);
    string left = plaintext.substr(0, 4);
    string right = plaintext.substr(4, 4);
    left = xor_operation(left, f_function(right, k1));
    swap(left, right);
    left = xor_operation(left, f_function(right, k2));
    string ciphertext = permute(left + right, IP_INV, 8);
    return ciphertext;
}

string decrypt(string ciphertext, string key) {
    string k1, k2;
    generate_keys(key, k1, k2);
    ciphertext = permute(ciphertext, IP, 8);
    string left = ciphertext.substr(0, 4);
    string right = ciphertext.substr(4, 4);
    left = xor_operation(left, f_function(right, k2));
    swap(left, right);
    left = xor_operation(left, f_function(right, k1));
    string plaintext = permute(left + right, IP_INV, 8);
    return plaintext;
}

int main() {
    string plaintext = "10101010";
    string key = "1010000010";
    string encrypted = encrypt(plaintext, key);
    string decrypted = decrypt(encrypted, key);
    
    cout << "Plaintext: " << plaintext << endl;
    cout << "Encrypted: " << encrypted << endl;
    cout << "Decrypted: " << decrypted << endl;
    
    return 0;
}
