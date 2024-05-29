#ifndef LZW_H
#define LZW_H

#include <string>
#include <vector>
#include <unordered_map>

class LZW {
public:
    std::vector<int> compress(const std::string &input);
    std::string decompress(const std::vector<int> &compressed);
};

#endif // LZW_H
