#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <cmath>
#include "array.h"

Array* array_create_and_read(std::ifstream& input)
{
    size_t n;
    input >> n;
    /* Create array */
    Array* arr = array_create(n);
    /* Read array data */
    for (size_t i = 0; i < n; ++i)
    {
        Data x;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array* arr)
{
    if (array_size(arr) != 30)
    {
        std::cout << "Error: array must contain 30 elements for June precipitation analysis.\n";
        return;
    }

    Data sum_first_half = 0;
    for (size_t i = 0; i < 15; i++)
    {
        sum_first_half += array_get(arr, i);
    }

    Data sum_second_half = 0;
    for (size_t i = 15; i < 30; i++)
    {
        sum_second_half += array_get(arr, i);
    }

    if (sum_first_half > sum_second_half)
    {
        std::cout << "More precipitation in the first half of June.\n";
    }
    else if (sum_second_half > sum_first_half)
    {
        std::cout << "More precipitation in the second half of June.\n";
    }
    else
    {
        std::cout << "Precipitation in both halves of June is equal.\n";
    }

    Data sum_dec1 = 0;
    for (size_t i = 0; i < 10; i++)
    {
        sum_dec1 += array_get(arr, i);
    }

    Data sum_dec2 = 0;
    for (size_t i = 10; i < 20; i++)
    {
        sum_dec2 += array_get(arr, i);
    }

    Data sum_dec3 = 0;
    for (size_t i = 20; i < 30; i++)
    {
        sum_dec3 += array_get(arr, i);
    }

    if (sum_dec1 >= sum_dec2 && sum_dec1 >= sum_dec3)
    {
        std::cout << "The most precipitation in the first decade of the month.\n";
    }
    else if (sum_dec2 >= sum_dec1 && sum_dec2 >= sum_dec3)
    {
        std::cout << "The most precipitation in the second decade of the month.\n";
    }
    else
    {
        std::cout << "The most precipitation in the third decade of the month.\n";
    }
}

void task2(Array* arr)
{
    std::vector<Data> evens;
    for (size_t i = 0; i < array_size(arr); i++)
    {
        Data val = array_get(arr, i);
        if (val % 2 == 0)
        {
            evens.push_back(val);
        }
    }

    if (evens.size() < 2)
    {
        std::cout << "Not enough even elements to calculate the difference.\n";
        return;
    }

    Data min_diff = std::numeric_limits<Data>::max();
    for (size_t i = 0; i < evens.size(); i++)
    {
        for (size_t j = i + 1; j < evens.size(); j++)
        {
            Data diff = std::abs(evens[i] - evens[j]);
            if (diff < min_diff)
            {
                min_diff = diff;
            }
        }
    }

    std::cout << min_diff << "\n";
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    Array* arr = NULL;
    std::ifstream input(argv[1]);
    if (!input.is_open())
    {
        std::cout << "Error opening file.\n";
        return 1;
    }

    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);
    input.close();
    return 0;
}