#include <iostream>
#include <fstream>
#include <cstdlib>
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

void task1(Array *arr)
{
    size_t size = array_size(arr);
    if (size == 0)
    {
        std::cout << 0 << std::endl;
        return;
    }

    int max_val = array_get(arr, 0);
    for (size_t i = 1; i < size; ++i)
    {
        int val = array_get(arr, i);
        if (val > max_val)
        {
            max_val = val;
        }
    }

    int count = 0;
    for (size_t i = 0; i < size; ++i)
    {
        if (std::abs(array_get(arr, i)) > max_val)
        {
            count++;
        }
    }

    std::cout << count << std::endl;
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

    task1(arr);
    array_delete(arr);
    input.close();
    return 0;
}