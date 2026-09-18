#include <iostream>
#include <fstream>
#include "array.h"


Array *array_create_and_read(std::ifstream& input)
{
    int n = 0;
    input >> n;
    Array* arr = array_create(n);
    for (int i = 0; i < n; ++i) {
        int x = 0;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array *arr, int a, int b)
{
    size_t n = array_size(arr);
    size_t write = 0;

    for (size_t i = 0; i < n; i++) {
        int v = array_get(arr, i);
        if (v < a || v > b) {
            array_set(arr, write, v);
            write++;
        }
    }

    for (size_t i = write; i < n; i++) {
        array_set(arr, i, 0);
    }

    for (size_t i = 0; i < n; i++) {
        std::cout << array_get(arr, i);
        if (i + 1 < n) std::cout << " ";
    }
    std::cout << "\n";
}

int main(int argc, char **argv)
{
    std::ifstream input(argv[1]);
    int a = 0, b = 0;
    input >> a >> b;
    Array* arr = array_create_and_read(input);
    task1(arr, a, b);
    array_delete(arr);
    input.close();
    return 0;
}