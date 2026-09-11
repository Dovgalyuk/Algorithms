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
    int current_sum = 0;
    for (size_t i = 0; i < 5; ++i)
    {
        current_sum += array_get(arr, i);
    }
    int max_sum = current_sum; size_t max_index = 0;
    for (size_t i = 5; i < n; ++i)
    {
        current_sum -= array_get(arr, i - 5);
        current_sum += array_get(arr, i);
        if (current_sum > max_sum)
        {
            max_sum = current_sum;
            max_index = i - 4;
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