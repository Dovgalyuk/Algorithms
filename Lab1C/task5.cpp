#include <iostream>
#include <fstream>
#include "array.h"

Array *array_create_and_read(std::ifstream& input)
{
    int n = 0;
    if (!(input >> n) or n <= 0) {
        std::cerr << "Error\n";
        return nullptr;
    }
    Array *arr = array_create(n);
    for (int i = 0 ; i < n ; ++i) {
        int x = 0;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}

void task5_array_rle(Array *arr) {
    size_t n = array_size(arr);
    size_t count = 1;
    int value = array_get(arr, 0);
    for (size_t i = 1; i < n ; ++i) {
        int current = array_get(arr, i);
        if (current == value) count++;
        else {
                std::cout << count << " " << value << " ";
            value = current;
            count = 1;
        };
    }
    std::cout << count << " " << value;
}

int main(int argc, char **argv) {
    if (argc < 2 or argc > 3) {
        std::cerr << "Error\n";
        return 1;
    }
    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Error\n";
        return 1;
    }
    Array* arr = array_create_and_read(input);
    task5_array_rle(arr);
    array_delete(arr);
    input.close();
}