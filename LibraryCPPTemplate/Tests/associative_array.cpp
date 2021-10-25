#include <iostream>
#include "associative_array.h"

typedef AssociativeArray<int, int> Array;

int main() {
    auto* array = new Array();
    int count = 1000000;
    for (size_t i = 0; i < count; i++)
    {
        array->insert(i, i);
        if (!array->isCorrectAVLTree()) {
            std::cout << "Incorrect adding to an associative array.";
            return 1;
        }
    }

    for (int i = 0; i < 15; ++i) {
        int key = rand() % (count * 2);
        if ((array->find(key) == key) != (key < count)) {
            std::cout << "Invalid search on associative array.";
            return 1;
        }
    }

    for (size_t i = 0; i < count; i++)
    {
        array->remove(i);
        if (!array->isCorrectAVLTree()) {
            std::cout << "Incorrect deletion from an associative array.  " << i;
            return 1;
        }
    }
    return 0;
}