#include "LZW.h"
#include <stdexcept>  // Incluir stdexcept para std::runtime_error

std::vector<int> LZW::compress(const std::string &input) {
    std::unordered_map<std::string, int> dictionary;
    for (int i = 0; i < 256; ++i) {
        dictionary[std::string(1, i)] = i;
    }

    std::string w;
    std::vector<int> compressed;
    for (char c : input) {
        std::string wc = w + c;
        if (dictionary.count(wc)) {
            w = wc;
        } else {
            compressed.push_back(dictionary[w]);
            dictionary[wc] = dictionary.size();
            w = std::string(1, c);
        }
    }

    if (!w.empty()) {
        compressed.push_back(dictionary[w]);
    }

    return compressed;
}

std::string LZW::decompress(const std::vector<int> &compressed) {
    std::unordered_map<int, std::string> dictionary;
    for (int i = 0; i < 256; ++i) {
        dictionary[i] = std::string(1, i);
    }

    std::string w(1, compressed[0]);
    std::string result = w;
    std::string entry;
    for (size_t i = 1; i < compressed.size(); ++i) {
        int k = compressed[i];
        if (dictionary.count(k)) {
            entry = dictionary[k];
        } else if (k == static_cast<int>(dictionary.size())) {  // Corregir la comparación
            entry = w + w[0];
        } else {
            throw std::runtime_error("Bad compressed k");
        }

        result += entry;
        dictionary[dictionary.size()] = w + entry[0];
        w = entry;
    }

    return result;
}
