#include "array.h"

struct Array
{
    int* data_;
    size_t size_;


    Array(size_t size) {
        data_ = new int[size];
        size_ = size;
    }

    ~Array(){
        delete[] data_;
    }
};


// create array
Array *array_create(size_t size)
{
    Array* arr = new Array(size);
    return arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    return arr->data_[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    arr->data_[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return  arr->size_;
}
