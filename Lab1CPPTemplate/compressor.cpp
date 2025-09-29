#include <iostream>
#include <fstream>
#include "utility.h"

Array<int> readDataForCompressor(const char* filename) {
    std::ifstream fin(filename);

    size_t size;
    fin >> size;

    Array<int> arr(size);
    for (size_t i = 0; i < size; ++i) {
        int value;
        fin >> value;
        arr.set(i, value);
    }

    int a, b;
    fin >> a >> b;
    fin.close();

    size_t writeIndex = 0;

    for (size_t i = 0; i < arr.size(); ++i) {
        int val = arr.get(i);
        if (val < a || val > b) {
            arr.set(writeIndex, val);
            ++writeIndex;
        }
    }

    for (size_t i = writeIndex; i < arr.size(); ++i) {
        arr.set(i, 0);
    }

    return arr;
}

int main(int argc, char** argv) {
    if (argc <= 1) {
        std::cerr << "Не хватает аргументов командной строки!" << std::endl;
        return 1;
    }

    Array<int> arr = readDataForCompressor(argv[1]);
    printArray(arr);

    return 0;
}