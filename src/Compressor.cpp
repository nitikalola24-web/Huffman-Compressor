#include "Compressor.h"
#include "Utils.h"
#include <iostream>
#include <chrono>
#include <cstdio>

static long getFileSize(const std::string& filename) {
    FILE* f = fopen(filename.c_str(), "rb");
    if (!f) return -1;
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    return size;
}

std::string Compressor::encode(const std::string& text, const std::unordered_map<char, std::string>& codes) {
    std::string encoded = "";
    for (char c : text)
        encoded += codes.at(c);
    return encoded;
}

void Compressor::showStatistics(const std::string& original, const std::string& encoded,
                                 double seconds, double throughputMB) {
    int originalBits = original.size() * 8;
    int encodedBits  = encoded.size();
    double ratio     = 100.0 * (1.0 - (double)encodedBits / originalBits);

    std::cout << "\n--- Compression Statistics ---\n";
    std::cout << "Original characters : " << original.size() << "\n";
    std::cout << "Original bits       : " << originalBits << "\n";
    std::cout << "Encoded bits        : " << encodedBits << "\n";
    std::cout << "Compression ratio   : " << ratio << "%\n";
    std::cout << "Time taken          : " << seconds << " seconds\n";
    std::cout << "Throughput          : " << throughputMB << " MB/s\n";
}

void Compressor::compress(const std::string& inputFile, const std::string& outputFile) {
    long fileSize     = getFileSize(inputFile);
    double fileSizeMB = fileSize / (1024.0 * 1024.0);

    std::cout << "\n--- File Info ---\n";
    std::cout << "File size           : " << fileSizeMB << " MB\n";
    std::cout << "Supported range     : up to 200MB (recommended under 50MB)\n";

    if (fileSize == 0) {
        std::cerr << "Error: File is empty.\n";
        return;
    }
    if (fileSize > 50 * 1024 * 1024) {
        std::cerr << "Warning: File exceeds 50MB. Large files may use significant RAM.\n";
    }
    if (fileSize > 200 * 1024 * 1024) {
        std::cerr << "Error: File too large. Max supported size is 200MB.\n";
        return;
    }

    std::string text = readFile(inputFile);
    if (text.empty()) { std::cerr << "Input file is empty.\n"; return; }

    HuffmanTree tree;
    tree.build(text);

    std::cout << "\n--- Huffman Codes ---\n";
    for (auto& pair : tree.codes)
        std::cout << "'" << pair.first << "' -> " << pair.second << "\n";

    auto start = std::chrono::high_resolution_clock::now();

    std::string encoded = encode(text, tree.codes);

    auto end        = std::chrono::high_resolution_clock::now();
    double seconds      = std::chrono::duration<double>(end - start).count();
    double throughputMB = (text.size() / (1024.0 * 1024.0)) / seconds;

    std::string toWrite = "";
    toWrite += std::to_string(tree.codes.size()) + "\n";
    for (auto& pair : tree.codes)
        toWrite += pair.first + std::string(" ") + pair.second + "\n";
    toWrite += encoded;

    writeFile(outputFile, toWrite);
    showStatistics(text, encoded, seconds, throughputMB);
    std::cout << "\nCompressed -> " << outputFile << "\n";
}