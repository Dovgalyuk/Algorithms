#include "array.h"

#include <fstream>
#include <iostream>


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "usage: means <input_file>";
        return 1;
    }

    std::ifstream input(argv[1]);

    if (!input)
    {
        std::cout << "cannot open file";
        return 1;
    }

    int n;

    if (!(input >> n) || n < 0)
    {
        std::cout << "invalid array size";
        return 1;
    }

    size_t size = static_cast<size_t>(n);
    Array* arr = array_create(size);

    for (size_t i = 0; i < array_size(arr); ++i)
    {
        Data value;

        if (!(input >> value))
        {
            std::cout << "invalid array element\n";
            array_delete(arr);
            return 1;
        }

        array_set(arr, i, value);
    }

    double positive_sum = 0;
    double negative_sum = 0;

    size_t positive_count = 0;
    size_t negative_count = 0;

    for (size_t i = 0; i < array_size(arr); ++i)
    {
        Data value = array_get(arr, i);

        if (value > 0)
        {
            positive_sum += value;
            ++positive_count;
        }
        else if (value < 0)
        {
            negative_sum += value;
            ++negative_count;
        }
    }

    if (positive_count > 0)
    {
        std::cout << "positive: "
                << positive_sum / positive_count
                << '\n';
    }
    else
    {
        std::cout << "positive: NONE\n";
    }

    if (negative_count > 0)
    {
        std::cout << "negative: "
                << negative_sum / negative_count
                << '\n';
    }
    else
    {
        std::cout << "negative: NONE\n";
    }

    array_delete(arr);

    return 0;
}