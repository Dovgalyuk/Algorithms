#include "array.h"

struct Array
{
    Data* data;
    size_t size;
};

// create array
Array *array_create(size_t size)
{
    std::unique_ptr<Array> arr(new Array);
    arr->data = new Data[size];
    arr->size = size;

    for(size_t i = 0; i < size; i++)
        arr->data[i] = 0;

    return arr.release();
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
    if(index < arr->size)
        return arr->data[index];     
    else 
    {
        std::cerr << "Index out of bounds: " << index << std::endl;
        return (Data)0;
    }
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if(index < arr->size)
        arr->data[index] = value;
    else 
        std::cerr << "Index out of bounds: " << index << std::endl;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->size;
}
