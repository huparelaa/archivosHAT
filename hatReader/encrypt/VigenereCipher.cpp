#include "VigenereCipher.h"
#include <stdexcept>

VigenereCipher::VigenereCipher(const std::string& key) {
    if (key.empty()) {
        throw std::invalid_argument("Key cannot be empty.");
    }
    this->key = key;
}

std::string VigenereCipher::encrypt(const std::string& text) {
    std::string output;
    output.reserve(text.size());

    for (size_t i = 0, j = 0; i < text.size(); ++i) {
        char plain_char = text[i];
        char key_char = key[j % key.size()];
        char encrypted_char = static_cast<char>(((unsigned char)plain_char + (unsigned char)key_char) % 256);
        output.push_back(encrypted_char);
        j++;
    }
    return output;
}

std::string VigenereCipher::decrypt(const std::string& text) {
    std::string output;
    output.reserve(text.size());

    for (size_t i = 0, j = 0; i < text.size(); ++i) {
        char encrypted_char = text[i];
        char key_char = key[j % key.size()];
        char decrypted_char = static_cast<char>(((unsigned char)encrypted_char - (unsigned char)key_char + 256) % 256);
        output.push_back(decrypted_char);
        j++;
    }
    return output;
}
