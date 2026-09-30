#include "array.h"

#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
        return 1;

    ifstream input(argv[1]);
    int size;
    if (!(input >> size) || size < 0)
        return 1;

    Array *arr = array_create(size);
    for (int i = 0; i < size; i++)
    {
        int value;
        if (!(input >> value))
        {
            array_delete(arr);
            return 1;
        }
        array_set(arr, i, value);
    }

    int left, right;
    if (!(input >> left >> right) || left > right)
    {
        array_delete(arr);
        return 1;
    }

    int new_size = 0;
    for (int i = 0; i < size; i++)
    {
        int value = array_get(arr, i);
        if (value < left || value > right)
            array_set(arr, new_size++, value);
    }

    for (int i = new_size; i < size; i++)
        array_set(arr, i, 0);

    for (int i = 0; i < size; i++)
    {
        if (i > 0)
            cout << ' ';
        cout << array_get(arr, i);
    }
    cout << '\n';

    array_delete(arr);
    return 0;
}
