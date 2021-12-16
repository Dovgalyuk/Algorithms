#include <iostream>
#include <ctime>
#include "array.h"

int input_size() {
    int size;
    std::cout << "Array size: ";
    std::cin >> size;
    return size;
}


void fill_container(Array* array) {

    std::srand(std::time(nullptr));
    for (int i = 0; i < array_size(array); i++) {
        array_set(array, i, rand() % 10);
    }
}

int aliquot(Array* array) {
    int amount = 0;
    for (int i = 0; i < array_size(array); i++) {
        for (int j = 2; j < 10; j++) {
            if (array_get(array, i) % j == 0) {
                amount++;
                j = 10;
            }
        }
    }
    return amount;

}

void print_array(Array* array) {
    for (int i = 0; i < array_size(array); i++) {
        std::cout << array_get(array, i) << " ";
    }
}

int main() {
    int size = input_size();
    Array* array = array_create(size);
    fill_container(array);
    //  print_array(array);
    std::cout << "\nNumber of multiples from 2 to 9: " << aliquot(array);
    array_delete(array);
    return 0;
}