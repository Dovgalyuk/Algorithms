#pragma once
#include "array.h"

template <typename T>
void printArray(const Array<T>& arr) {
    for (size_t i = 0; i < arr.size(); ++i)
    {
        std::cout << arr.get(i) << " ";
    }
    std::cout << std::endl;
}
