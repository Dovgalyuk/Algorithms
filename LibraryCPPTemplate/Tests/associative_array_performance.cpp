#include <iostream>
#include "associative_array.h"
#include <vector>

typedef AssociativeArray<int, int> Array;

int main() {
    Array array;
    int count = 5000000;
    for (size_t i = 0; i < count; i++)
    {
        array.insert(i, i);
    }

    for (int i = 0; i < 15; ++i) {
        int key = rand() % (count * 2);
        if ((array.find(key) == key) != (key < count)) {
            std::cout << "Invalid search on associative array.";
            return 1;
        }
    }

    for (size_t i = 0; i < count; i++)
    {
        array.remove(i);
    }

    if (!array.isEmpty()) {
        std::cout << "Incorrect deletion from an associative array. ";
        return 1;
    }
    return 0;
}