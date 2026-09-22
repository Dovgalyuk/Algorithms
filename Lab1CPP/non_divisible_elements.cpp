#include <iostream>
#include <fstream>
#include "array.h"

bool read_array(std::ifstream& input, Array<int>& array)
{
    for (size_t i = 0; i < array.size(); ++i)
    {
        int value;
        if (!(input >> value))
        {
            return false;
        }
        array.set(i, value);
    }

    return true;
}

bool divisible_by_other(const Array<int>& array, size_t index)
{
    int value = array.get(index);

    for (size_t j = 0; j < array.size(); ++j)
    {
        int y = array.get(j);
        if (j != index && y != 0 && value % y == 0)
        {
            return true;
        }
    }

    return false;
}

void print_not_divisible(const Array<int>& array)
{
    for (size_t i = 0; i < array.size(); ++i)
    {
        if (!divisible_by_other(array, i))
        {
            std::cout << array.get(i) << ' ';
        }
    }
    std::cout << std::endl;
}

int main(int argc, char** argv)
{
    if (argc <= 1)
    {
        std::cerr << "Missing command-line arguments" << std::endl;
        return 1;
    }

    std::ifstream fin(argv[1]);

    size_t size;
    if (!(fin >> size))
    {
        std::cerr << "Cannot read array size" << std::endl;
        return 1;
    }

    Array<int> array(size);
    if (!read_array(fin, array))
    {
        std::cerr << "Cannot read array elements" << std::endl;
        return 1;
    }

    print_not_divisible(array);

    return 0;
}