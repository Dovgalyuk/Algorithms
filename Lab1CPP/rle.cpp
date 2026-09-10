#include <fstream>
#include <iostream>
#include "array.h"


using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: rle <input_file>\n";
        return 1;
    }

    ifstream input(argv[1]);

    if (!input)
    {
        std::cerr << "Cannot open file\n";
        return 1;
    }

    int size;
    if (!(input >> size) || size < 0)
    {
        std::cerr << "Invalid array size\n";
        return 1;
    }

    Array* arr = array_create(size);

    for (int i = 0; i < size; ++i)
    {
        int value;
        if (!(input >> value))
        {
            std::cerr << "Invalid input data\n";
            array_delete(arr);
            return 1;
        }
        array_set(arr, i, value);
    }

    size_t groups = 0;

    if (size > 0)
    {
        groups = 1;

        for (int i = 1; i < size; ++i)
        {
            if (array_get(arr, i) != array_get(arr, i - 1))
                ++groups;
        }
    }

    Array* result = array_create(groups * 2);
    size_t position = 0;

    if (size > 0)
    {
        int current = array_get(arr, 0);
        int count = 1;

        for (int i = 1; i < size; ++i)
        {
            int value = array_get(arr, i);
            if (value == current)
            {
                ++count;
            }
            else
            {
                array_set(result, position, current);
                array_set(result, position + 1, count);
                position += 2;

                current = value;
                count = 1;
            }
        }

        // последняя группа
        array_set(result, position, current);
        array_set(result, position + 1, count);
    }

   for (size_t i = 0; i < array_size(result); i += 2)
    {
        cout << array_get(result, i) << ' ' << array_get(result, i + 1) << '\n';
    }

    array_delete(arr);
    array_delete(result);
    return 0;
}