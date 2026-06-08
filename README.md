# Huffman Compressor

A command-line file compression tool using the Huffman coding algorithm, written in C++.

## Build

```bash
g++ -o huff src/main.cpp src/HuffmanTree.cpp src/Compressor.cpp src/Decompressor.cpp src/Utils.cpp
```

## Usage

```bash
./huff compress   input.txt  encoded.txt
./huff decompress encoded.txt output.txt
```

## Project Structure

- `Node.h` — Tree node and comparator
- `HuffmanTree` — Builds tree, generates codes
- `Compressor` — Encodes text, writes compressed file
- `Decompressor` — Reads compressed file, decodes text
- `Utils` — File read/write helpers