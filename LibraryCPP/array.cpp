#include "array.h"

struct Array
{
    Data data;
    size_t size;
};

// create array
Array array_create(size_t size)
{
    Array newArr;
    newArr.data = new Data[size];
    newArr.size = size;
    return newArr;
}

// delete array, free memory
void array_delete(Array arr)
{
    delete[] arr.data;
}

// returns specified array element
Data array_get(const Array arr, size_t index)
{
    if (index < arr.size) {
        return arr.data[index];
    }
    else {
        // handle out of bounds error
        return Data(); // return default value for Data type
    }
}

// sets the specified array element to the value
void array_set(Array arr, size_t index, Data value)
{
    if (index < arr.size) {
        arr.data[index] = value;
    }
    else {
        // handle out of bounds error
    }
}

// returns array size
size_t array_size(const Array arr)
{
    return arr->size;
}