#include <iostream>
#include <fstream>
#include "array.h"

Array *array_create_and_read(std::ifstream& input)
{
    size_t n;
    input >> n;
    Array* arr = array_create(n);

    for (size_t i = 0 ; i < n ; ++i)
    {
        int x;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array *arr)
{
    int sigh = 0;
    size_t size = array_size(arr);

    for (size_t i = 1; i < size; i++) {
        if ((array_get(arr, i - 1) < 0 && array_get(arr, i) > 0) ||
            (array_get(arr, i - 1) > 0 && array_get(arr, i) < 0)) {
            sigh++;
        }
    }
    std::cout << sigh << std::endl;
}

void task2(Array *arr)
{
    size_t size = array_size(arr);
    if (size < 2) {
        return;
    }
    size_t min_index = 0, max_index = 0;
    for (size_t i = 1; i < size; i++) {
        if (array_get(arr, i) < array_get(arr, min_index)) {
            min_index = i;
        }
        if (array_get(arr, i) > array_get(arr, max_index)) {
            max_index = i;
        }
    }
    if (min_index > max_index) {
        std::swap(min_index, max_index);
    }
    int sum = 0;
    for (size_t i = min_index + 1; i < max_index; ++i) {
        sum += array_get(arr, i);
    }
    std::cout << sum << std::endl;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input) {
        return 1;
    }
    Array* arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);

    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);

    input.close();
    return 0;
}
