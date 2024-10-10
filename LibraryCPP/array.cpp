#include "array.h"
#include <stdexcept>

struct Array
{
    Data* data;
    size_t size;
};

// create array
Array *array_create(size_t size)
{
    size_t ms = 1000000;  
    if (size > ms) {
        throw std::overflow_error("sloshkom bolshoy razmer");
    }
    Array* arr = new Array;
    arr->data = new Data[size];
    arr->size = size;
    return arr;

}

// delete array, free memory
void array_delete(Array *arr)
{
    delete[] arr->data;
    delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    arr->data[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->size;
}

Array* array_rand(std::ifstream& vvod) {

    Data znach;
    size_t si;
    vvod >> si;
    Array* array = array_create(si);
    for (size_t i = 0; i < si; i++) {

        vvod >> znach;
        array_set(array, i, znach);
    }
    return array;
}

