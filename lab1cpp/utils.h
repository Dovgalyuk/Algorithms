#pragma once

#include "array.h"

#include <fstream>
#include <stdexcept>
#include <string>

typedef Array<int> MyArray;

inline MyArray readArrayFromFile(const std::string& fileName)
{
    std::ifstream input(fileName);

    if (!input.is_open()) {
        throw std::runtime_error("Cannot open input file");
    }

    int n;
    input >> n;

    if (!input || n < 0) {
        throw std::runtime_error("Incorrect array size");
    }

    MyArray arr(n);

    for (int i = 0; i < n; ++i) {
        int value;
        input >> value;

        if (!input) {
            throw std::runtime_error("Not enough numbers in input file");
        }

        arr.set(i, value);
    }

    return arr;
}