#ifndef HUFFMANCODE_H
#define HUFFMANCODE_H

#include <fstream>

void huffman_compress(std::ifstream& fileIn, const std::string& compressedFileName);

void huffman_decompress(std::ifstream& fileIn, const std::string& decompressedFileName);

#endif