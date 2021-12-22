#include <iostream>
#include <ctime>
#include "associative_array.h"

int main() {
    AssociativeArray<int> array;
    int amount = 10000000;
    for (int i = 0; i < amount; ++i) {
        array.insert(std::to_string(i), i);
    }
    std::srand(std::time(0));
    for (int i = 0; i < 5; ++i) {
        int index = rand() % amount;
        std::string str = std::to_string(index);
        auto* node = array.findNode(str);
        if (!node || node->data != index) {
            std::cout << "The data in the associative array is not stored correctly.\n" << index << "   " << ((node) ? node->data : -1);
            return 1;
        }
    }
    for (int i = 0; i < 5; ++i) {
        int index = rand() % amount;
        array.remove(std::to_string(index));
        std::string str = std::to_string(index);
        auto* node = array.findNode(str);
        if (node) {
            std::cout << "Removing from an associative array does not work correctly.\n";
            return 1;
        }
    }
}