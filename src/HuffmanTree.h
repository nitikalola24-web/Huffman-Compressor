#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "Node.h"
#include <unordered_map>
#include <string>

class HuffmanTree {
public:
    Node* root;
    std::unordered_map<char, std::string> codes;

    HuffmanTree();
    void build(const std::string& text);
    void generateCodes(Node* node, const std::string& path);
    void deleteTree(Node* node);
    ~HuffmanTree();

private:
    std::unordered_map<char, int> buildFrequencyTable(const std::string& text);
};

#endif