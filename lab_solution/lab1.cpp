#include <iostream>
#include <ctime>
#include "array.h"

int size_array() {
    int size;
    std::cout << "Size of arr: ";
    std::cin >> size;
    return size;
}


void fill_array(Array* array) {
    std::srand(std::time(NULL));
    for (int i = 0; i < array_size(array); i++) {
        array_set(array, i, rand() % 10);
    }
}



void print(Array* array) {
    for (int i = 0; i < array_size(array); i++) {
        std::cout << array_get(array, i) << " ";
    }
    std::cout << "\n";
}


void find_matches(Array* array) {
    int a[10] {};
    for (int i = 0; i < array_size(array); i++) {
        int k = array_get(array, i);
        a[k]++;
    }
    bool is_matches = false;
    for (int j = 0; j < 10; j++)
    {
        if (a[j] == 2) {
            is_matches = true;
            std::cout << j << " ";
        }
    }
    if (!is_matches) std::cout << "No matches found.";
}

int main() {
    int size = size_array();
    Array* arr = array_create(size);
    fill_array(arr);
    print(arr);
    find_matches(arr);
    array_delete(arr);
}