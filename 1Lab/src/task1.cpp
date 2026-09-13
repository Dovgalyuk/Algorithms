#include "../include/array.h"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    // reading variables

    if (argc != 2)
    {
        std::cerr << "There must be 2 entered arguments" << std::endl;
        return 1;
    }

    std::ifstream in(argv[1]);

    if (!in.is_open())
    {
        std::cerr << "Cannot open file " << argv[1] << std::endl;
        return 1;
    }

    // first array

    size_t array_size;

    if (!(in >> array_size))
    {
        std::cerr << "Failed to read size" << std::endl;
        return 1;
    }

    array<int> arr1(array_size);
    size_t array2_size = 0;

    for (size_t i = 0; i < array_size; i++)
    {
        if (!(in >> arr1[i]))
        {
            std::cerr << "Failed to read element" << std::endl;
            return 1;
        }

        if (arr1[i] % 2 == 0)
        {
            array2_size++;
        }
    }

    // second array

    array<int> arr2(array2_size);
    size_t counter = 0;

    for (size_t i = 0; i < array_size; i++)
    {
        if (arr1[i] % 2 == 0)
        {
            arr2[counter] = static_cast<int>(i);
            counter++;
        }
    }

    // output

    // all elements

    for (size_t i = 0; i < array_size; i++)
    {
        std::cout << arr1[i] << " ";
    }

    std::cout << '\n';

    // index of even elements

    for (size_t i = 0; i < array2_size; i++)
    {
        std::cout << arr2[i] << " ";
    }

    std::cout << '\n';

    return 0;
}