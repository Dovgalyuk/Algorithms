#include "huffman.h"
#include <sstream>
#include <iostream>

void testHuffmanEncodeDecode(const std::string& testString) {
    Huffman huffman;
    std::istringstream input(testString);
    std::ostringstream encodedOutput;

    huffman.encode(input, encodedOutput);

    std::string encodedString = encodedOutput.str();
    if (encodedString.empty()) {
        std::cerr << "Test failed: Encoding output is empty for string \"" << testString << "\"" << std::endl;
        exit(1);
    }

    std::istringstream encodedInput(encodedString);
    std::ostringstream decodedOutput;

    huffman.decode(encodedInput, decodedOutput);

    std::string decodedString = decodedOutput.str();
    if (decodedString != testString) {
        std::cerr << "Test failed: Decoded string \"" << decodedString
            << "\" does not match original string \"" << testString << "\"" << std::endl;
        exit(1);
    }
}

int main() {
    testHuffmanEncodeDecode("Hello, Huffman encoding!");
    testHuffmanEncodeDecode("Another test string with different characters & symbols.");

    std::cout << "All Huffman tests passed successfully." << std::endl;
    return 0;
}