#include "Decompressor.h"
#include "Utils.h"
#include <sstream>
#include <iostream>

Node* Decompressor::buildTreeFromCodes(const std::unordered_map<char, std::string>& codes) {
    Node* root = new Node('\0', 0);
    for (auto& pair : codes) {
        Node* curr = root;
        for (char bit : pair.second) {
            if (bit == '0') {
                if (!curr->left)  curr->left  = new Node('\0', 0);
                curr = curr->left;
            } else {
                if (!curr->right) curr->right = new Node('\0', 0);
                curr = curr->right;
            }
        }
        curr->ch = pair.first;
    }
    return root;
}

std::string Decompressor::decode(const std::string& bits, Node* root) {
    std::string result = "";
    Node* curr = root;
    for (char bit : bits) {
        curr = (bit == '0') ? curr->left : curr->right;
        if (!curr->left && !curr->right) {
            result += curr->ch;
            curr = root;
        }
    }
    return result;
}

void Decompressor::decompress(const std::string& inputFile, const std::string& outputFile) {
    std::string raw = readFile(inputFile);
    std::istringstream ss(raw);

    int mapSize;
    ss >> mapSize;
    ss.ignore();

    std::unordered_map<char, std::string> codes;
    for (int i = 0; i < mapSize; i++) {
        char ch;
        std::string code;
        ss.get(ch);
        ss >> code;
        ss.ignore();
        codes[ch] = code;
    }

    std::string bits;
    ss >> bits;

    Node* root      = buildTreeFromCodes(codes);
    std::string decoded = decode(bits, root);

    writeFile(outputFile, decoded);

    std::cout << "\n--- Decompression Statistics ---\n";
    std::cout << "Decoded characters  : " << decoded.size() << "\n";
    std::cout << "Restoration         : 100% (Huffman is lossless)\n";

    std::string originalText = readFile("samples/input.txt");
    if (!originalText.empty()) {
        bool match = (decoded == originalText);
        std::cout << "File integrity      : " << (match ? "PASSED" : "FAILED") << "\n";
    }

    std::cout << "\nDecompressed -> " << outputFile << "\n";
}