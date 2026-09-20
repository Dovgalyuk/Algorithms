#include <fstream>
#include <iostream>
#include "array.h"

using namespace std;
Array* read_array(const char* filename)
{
    ifstream input(filename);

    size_t size;
    input >> size;

    Array* arr = array_create(size);

    for (size_t i = 0; i < size; ++i)
    {
        Data value;
        input >> value;
        array_set(arr, i, value);
    }

    return arr;
}

int main(int argc, char** argv)
{
    if (argc < 2)
        return 1;

    Array* arr = read_array(argv[1]);

    bool first = true;

    for (size_t i = 0; i < array_size(arr); ++i)
    {
        Data value = array_get(arr, i);
        bool divisible = false;

        for (size_t j = 0; j < array_size(arr); ++j)
        {
            if (i == j)
                continue;

            Data other = array_get(arr, j);

            if (other != 0 && value % other == 0)
            {
                divisible = true;
                break;
            }
        }

        if (!divisible)
        {
            if (!first)
                cout << " ";

            cout << value;
            first = false;
        }
    }

    cout << endl;

    array_delete(arr);

    return 0;
}