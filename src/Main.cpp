#include <iostream>
#include "Compressor.h"
#include "Decompressor.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Usage:\n";
        std::cout << "  ./huff compress   input.txt  encoded.txt\n";
        std::cout << "  ./huff decompress encoded.txt output.txt\n";
        return 1;
    }

    std::string mode       = argv[1];
    std::string inputFile  = argv[2];
    std::string outputFile = argv[3];

    if (mode == "compress") {
        Compressor c;
        c.compress(inputFile, outputFile);
    } else if (mode == "decompress") {
        Decompressor d;
        d.decompress(inputFile, outputFile);
    } else {
        std::cerr << "Unknown mode: " << mode << "\n";
        return 1;
    }

    return 0;
}