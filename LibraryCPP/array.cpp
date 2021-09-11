#include "array.h"

struct Array
{
    size_t arr_size = 0;
    Data* arr_data = 0;
    Array(size_t arr_size) {
        this->arr_size = arr_size;
        this->arr_data = new Data[arr_size];
    }
};

// create array
Array *array_create(size_t size)
{   
    return new Array(size);
}

// delete array, free memory
void array_delete(Array* arr)
{
    delete[] arr;
    arr = nullptr;
}

// returns specified array element
Data array_get(const Array* arr, size_t index)
{

    return arr->arr_data[index];
}

// sets the specified array element to the value
void array_set(Array* arr, size_t index, Data value)
{
    arr->arr_data[index] = value;
}

// returns array size
size_t array_size(const Array* arr)
{
    return arr->arr_size;
}
