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

    size_t array_size;

    if (!(in >> array_size))
    {
        std::cerr << "Failed to read size" << std::endl;
        return 1;
    }

    int diretion;

    if (!(in >> diretion))
    {
        std::cerr << "Failed to read deriction" << std::endl;
        return 1;
    }

    // first array

    array<int> arr1(array_size);

    for (size_t i = 0; i < array_size; i++)
    {
        if (!(in >> arr1[i]))
        {
            std::cerr << "Failed to read element" << std::endl;
            return 1;
        }
    }

    // second array

    array<int> arr2(array_size);
    size_t counter;
    if (array_size > 0)
    {
        diretion %= static_cast<int>(array_size);
    }

    if (diretion >= 0)
    {
        size_t dir = static_cast<size_t>(diretion);
        counter = 0;
        for (size_t i = 0; i < array_size; i++)
        {
            if (i < dir)
            {
                arr2[i] = 0;
            }
            else
            {
                arr2[i] = arr1[counter];
                counter++;
            }
        }
    }
    else
    {
        size_t dir = static_cast<size_t>(-diretion);
        counter = dir;
        size_t boundary = array_size - dir;
        for (size_t i = 0; i < array_size; i++)
        {
            if (i < boundary)
            {
                arr2[i] = arr1[counter];
                counter++;
            }
            else
            {
                arr2[i] = 0;
            }
        }
    }

    // output

    // all elements
    for (size_t i = 0; i < array_size; i++)
    {
        std::cout << arr1[i] << " ";
    }

    std::cout << '\n';

    // shifted elements

    for (size_t i = 0; i < array_size; i++)
    {
        std::cout << arr2[i] << " ";
    }

    std::cout << '\n';

    return 0;
}