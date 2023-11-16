#ifndef HUFFMANCODE_H
#define HUFFMANCODE_H

#include <fstream>
#include <vector>
#include <map>

#include "array.h"
#include "priorityQueue.h"

typedef std::map<unsigned char, std::vector<bool>> symbolsTableMap;

void huffman_compress(std::ifstream& fileIn, const std::string& compressedFileName);

void huffman_decompress(std::ifstream& fileIn, const std::string& decompressedFileName);

#endif
