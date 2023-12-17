#include "huffman.h"
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "RUS");
    Huffman huffman;
   
    // ����������� �����
    ifstream inputFile("input.txt");
    ofstream encodedFile("encoded.bin", ios::binary);
    if (!inputFile.is_open() || !encodedFile.is_open()) {
        cerr << "������ ��� �������� ������ ��� �����������!" << endl;
        return 1;
    }

    huffman.encode(inputFile, encodedFile);
    inputFile.close();
    encodedFile.close();

    cout << "���� ������� �����������." << endl;

    // ������������� �����
    ifstream encodedInput("encoded.bin", ios::binary);
    ofstream decodedOutput("decoded.txt");
    if (!encodedInput.is_open() || !decodedOutput.is_open()) {
        cerr << "������ ��� �������� ������ ��� �������������!" << endl;
        return 1;
    }

    huffman.decode(encodedInput, decodedOutput);
    encodedInput.close();
    decodedOutput.close();

    cout << "���� ������� �����������." << endl;

}