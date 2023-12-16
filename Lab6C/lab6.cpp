#include "Huffman.h"
#include <fstream>
#include <iostream>

int main() {
    Huffman huffman;

    // ����������� �����
    std::ifstream inputFile("input.txt");
    std::ofstream encodedFile("encoded.bin", std::ios::binary);
    if (!inputFile.is_open() || !encodedFile.is_open()) {
        std::cerr << "������ ��� �������� ������ ��� �����������!" << std::endl;
        return 1;
    }

    huffman.encode(inputFile, encodedFile);
    inputFile.close();
    encodedFile.close();

    std::cout << "���� ������� �����������." << std::endl;

    // ������������� �����
    std::ifstream encodedInput("encoded.bin", std::ios::binary);
    std::ofstream decodedOutput("decoded.txt");
    if (!encodedInput.is_open() || !decodedOutput.is_open()) {
        std::cerr << "������ ��� �������� ������ ��� �������������!" << std::endl;
        return 1;
    }

    huffman.decode(encodedInput, decodedOutput);
    encodedInput.close();
    decodedOutput.close();

    std::cout << "���� ������� �����������." << std::endl;

    return 0;
}