#include <iostream>
#include <fstream>
#include "array.h"

Array* array_create_and_read(std::ifstream& input)
{
    int n = 0;
    if (input >> n) {
        Array* arr = array_create(n);
        for (int i = 0; i < n; ++i) {
            int x = 0;
            if (input >> x) {
                array_set(arr, i, x);
            }
        }
        return arr;
    }
    return nullptr;
}

void task1(Array* arr)
{
    if (!arr) return;
    size_t n = array_size(arr);

    size_t even_count = 0;
    for (size_t i = 0; i < n; ++i) {
        if (array_get(arr, i) % 2 == 0) {
            even_count++;
        }
    }

    Array* even_indices = array_create(even_count);

    size_t idx = 0;
    for (size_t i = 0; i < n; ++i) {
        if (array_get(arr, i) % 2 == 0) {
            array_set(even_indices, idx++, static_cast<Data>(i));
        }
    }

    for (size_t i = 0; i < array_size(even_indices); ++i) {
        std::cout << array_get(even_indices, i) << (i + 1 == array_size(even_indices) ? "" : " ");
    }
    std::cout << "\n";

    array_delete(even_indices);
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        return 1;
    }
    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        return 1;
    }
    Array* arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    input.close();
    return 0;
}