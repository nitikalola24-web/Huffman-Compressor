#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

#include "Node.h"
#include <string>
#include <unordered_map>

class Decompressor {
public:
    void decompress(const std::string& inputFile, const std::string& outputFile);

private:
    std::string decode(const std::string& bits, Node* root);
    Node* buildTreeFromCodes(const std::unordered_map<char, std::string>& codes);
};

#endif