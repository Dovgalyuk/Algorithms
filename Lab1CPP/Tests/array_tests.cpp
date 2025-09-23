#include <iostream>
#include <cassert>
#include "../array.h"

int main() {
    const std::size_t N = 100;

    Array* arr = new Array(N);

    for (std::size_t i = 0; i < N; ++i) {
        (*arr)[i] = static_cast<int>(i * 2);
    }

    Array copy = *arr;

    for (std::size_t i = 0; i < N; ++i) {
        assert((*arr)[i] == static_cast<int>(i * 2));
        assert(copy[i] == static_cast<int>(i * 2));
    }

    delete arr;
    std::cout << "Array basic tests passed\n";
    return 0;
}
