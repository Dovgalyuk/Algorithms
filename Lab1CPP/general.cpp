#include "general.h"

Array *read_file_and_create_array(ifstream &input)
{
    size_t size;
    input >> size;

    if (size <= 0) {
        return nullptr; // Return nullptr for an empty array
    }

    Array *arr = array_create(size);

    for (size_t i = 0; i < size; ++i) {
        int value;
        input >> value;
        array_set(arr, i, value);
    }

    return arr;
} 