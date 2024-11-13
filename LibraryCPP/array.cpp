#include "array.h"

struct Array
{
    Data* array;    
    size_t size;  
};

// create array
Array *array_create(size_t size)
{
    if(size !=  0) {
        Array* array = new Array;
        array->size = size;
        array->array = new Data[size];

        return array;
    }
    else {
        return nullptr;
    }
}

// delete array, free memory
void array_delete(Array *arr)
{
    if(arr->array != nullptr)  {
        delete[] arr->array;
        delete arr;
    }
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    if (index < arr->size)
        return arr->array[index];
    else
        return 0;
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (index < arr->size)
    {
        arr->array[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    if (arr->array != nullptr) {
        return arr->size;
    }
}
Array* fill_array(std::ifstream &input)
{
    size_t size;
    Data value;
    input >> size;
    Array* array = array_create(size);

    for (size_t i = 0; i < size; i++) {
        input >> value; 
        array_set(array, i, value);
    }

    return array;
}
