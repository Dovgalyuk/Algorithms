#include <iostream>
#include <ctime>
#include "associative_array.h"

int main() {
    AssociativeArray<int> array;
    int amount = 10000000;
    for (int i = 0; i < amount; ++i) {
        array.insert(i, i);
    }
    std::srand(std::time(0));
    for (int i = 0; i < 5; ++i) {
        int index = rand() % amount;
        int data = array.find(index);
        if (data != index) {
            std::cout << "The data in the associative array is not stored correctly.\n";
            return 1;
        }
    }
    for (int i = 0; i < 5; ++i) {
        int index = rand() % amount;
        array.remove(index);
        int data = array.find(index);
        if (data != NULL) {
            std::cout << "Removing from an associative array does not work correctly.\n";
            return 1;
        }
    }
}