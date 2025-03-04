#include <iostream>
#include "array.h"

int main()
{
    Array<int> arr(10);
    if (arr.size() != 10) {
        std::cerr << "Test Failed: Size is incorrect" << std::endl;
        return 1;
    }

    for (size_t i = 0; i < arr.size(); ++i) {
        arr[i] = i * 2;
    }

    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr.at(i) != i * 2) {
            std::cerr << "Test Failed: Value mismatch at index " << i << std::endl;
            return 1;
        }
    }

    bool exceptionCaught = false;
    try {
        arr.at(10);
    } catch (const std::out_of_range& e) {
        exceptionCaught = true;
    }

    if (!exceptionCaught) {
        std::cerr << "Test Failed: Out of range exception not caught" << std::endl;
        return 1;
    }

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
