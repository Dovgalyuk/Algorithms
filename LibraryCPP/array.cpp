#include <iostream>
#include "array.h"

using namespace std;

struct Array
{
    Data *data;
    size_t size;
};

// create array
Array *array_create(size_t size)
{
    if (size == 0) return nullptr;

    Array *container = new Array;
    container->size = size;
    container->data = new Data[size];
    return container;
}

// delete array, free memory
void array_delete(Array *arr)
{
    if (!arr) return;
    delete[] arr->data;
    arr->data = nullptr;
    delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    if (!arr) {
        cout << "Array_get: null array pointer\n";
        return 1;
    }
    if (index >= arr->size) {
        cout << "Array_get: index out of range\n";
        return 1;
    }
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (!arr) {
        cout << "Array_set: null array pointer";
        return;

    }
    if (index >= arr->size) {
        cout << "Array_set: index out of range";
        return;
    }

    arr->data[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr ? arr->size : 0;
}
