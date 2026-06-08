#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include "HuffmanTree.h"
#include <string>

class Compressor {
public:
    void compress(const std::string& inputFile, const std::string& outputFile);

private:
    std::string encode(const std::string& text, const std::unordered_map<char, std::string>& codes);
    void showStatistics(const std::string& original, const std::string& encoded,
                        double seconds, double throughputMB);
};

#endif