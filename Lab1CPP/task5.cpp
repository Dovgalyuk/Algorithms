#include <iostream>
#include <fstream>
#include "array.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Input file not specified";
        return 1;
    }

    std::ifstream input(argv[1]);
    if(!input){
        std::cout << "Failed open file!"; return 1;
    }
    size_t n; input>>n;
    if(n < 5){
        std::cout << "< 5 int"; return 1;
    }
    Array *arr = array_create(n);
    for (size_t i = 0; i < n; ++i)
    {
        int value;
        input >> value;
        array_set(arr, i, value);
    }
    int max_sum = 0;
    for (size_t i = 0; i < 5; ++i)
    {
        max_sum += array_get(arr, i);
    }
    size_t max_index = 0;
    for (size_t i = 1; i <= n - 5; ++i)
    {
        int sum = 0;
        for (size_t j = 0; j < 5; ++j)
        {
            sum += array_get(arr, i + j);
        }
        if (sum > max_sum)
        {
            max_sum = sum;
            max_index = i;
        }
    }
    std::cout << "Max sum: " << max_sum << "\n";
    std::cout << "Elements: ";
    for (size_t i = 0; i < 5; ++i)
    {
        std::cout << array_get(arr, max_index + i) << " ";
    }
    std::cout << "\n";
    array_delete(arr);
}