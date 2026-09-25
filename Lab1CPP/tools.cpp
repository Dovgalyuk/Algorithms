#include "tools.h"

Array *array_create_and_read(std::ifstream &input)
{
    int size;
    input >> size;

    if (size <= 0)
        return nullptr;

    Array *arr = array_create(size);

    for (int i = 0; i < size; i++)
    {
        int value;
        input >> value;
        array_set(arr, i, value);
    }
    return arr;
}