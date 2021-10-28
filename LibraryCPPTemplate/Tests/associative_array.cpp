#include <iostream>
#include "associative_array.h"
#include <vector>
#include <algorithm>

typedef AssociativeArray<int, int> Array;

int main() {
    Array array;
    int count = 5000;
    for (size_t i = 0; i < count; i++)
    {
        array.insert(i, i);
        if (!array.isCorrectAVLTree()) {
            std::cout << "Incorrect adding to an associative array.";
            return 1;
        }
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
        if (!array.isCorrectAVLTree() || (array.isEmpty() && count - i > 1)) {
            std::cout << "Incorrect deletion from an associative array. ";
            return 1;
        }
    }

    if (!array.isEmpty()) {
        std::cout << "Incorrect deletion from an associative array. ";
        return 1;
    }

    std::vector<int> keys;

    for (int i = 0; i < count; ++i) {
        int num;
        do {
            num = rand();
        } while (std::find(keys.begin(), keys.end(), num) != keys.end());
        keys.push_back(num);
        array.insert(num, num);
        if (!array.isCorrectAVLTree()) {
            std::cout << "Incorrect adding to an associative array.";
            return 1;
        }
    }

    std::vector<int> removedKeys;

    for (size_t i = 0; i < count; i++)
    {
        int id = rand() % keys.size();
        int key = keys[id];
        keys.erase(keys.begin() + id);
        array.remove(key);
        removedKeys.push_back(key);
        if (!array.isCorrectAVLTree() || (array.isEmpty() && count - i > 1)) {
            std::cout << "Incorrect deletion from an associative array. ";
            return 1;
        }
    }

    if (!array.isEmpty()) {
        std::cout << "Incorrect deletion from an associative array. ";
        return 1;
    }

    return 0;
}