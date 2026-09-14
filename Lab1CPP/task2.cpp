#include <iostream>
#include <fstream>
#include "array.h"

Array *read_file_and_create_array(std::ifstream &input)
{
    size_t size = 0;
    if (!(input >> size) || size == 0)
    {
        return nullptr;
    }

    Array *arr = array_create(size);
    for (size_t i = 0; i < size; ++i)
    {
        int value = 0;
        input >> value;
        array_set(arr, i, value);
    }
    return arr;
}

void task2(Array *arr)
{
    size_t size = array_size(arr);
    if (size < 5)
    {
        std::cerr << "Error: array must have at least 5 elements." << std::endl;
        return;
    }

    long long current_sum = 0;
    for (size_t i = 0; i < 5; ++i)
    {
        current_sum += array_get(arr, i);
    }

    long long max_sum = current_sum;
    size_t best_start_idx = 0;

    for (size_t i = 5; i < size; ++i)
    {
        current_sum += array_get(arr, i) - array_get(arr, i - 5);
        if (current_sum > max_sum)
        {
            max_sum = current_sum;
            best_start_idx = i - 4;
        }
    }

    for (size_t i = 0; i < 5; ++i)
    {
        if (i > 0)
        {
            std::cout << " ";
        }
        std::cout << array_get(arr, best_start_idx + i);
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open())
    {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

    Array *arr = read_file_and_create_array(input);
    if (arr == nullptr)
    {
        std::cerr << "Error reading array from file." << std::endl;
        return 1;
    }

    task2(arr);
    array_delete(arr);
    input.close();
    return 0;
}