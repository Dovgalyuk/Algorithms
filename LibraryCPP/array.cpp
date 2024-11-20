#include <iostream>
#include "../LibraryCPP/array.h"

struct Array
{
    Data* array_origin;
    size_t size;
};

// create array
Array *array_create(size_t size)
{
    if (size > 0){
        Array* array = new Array;
        if (!array) return nullptr;
        
        array->size = size;
        array->array_origin = new Data[size];
        
        return array;
    }
    else return nullptr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    if (arr) {
        delete[] arr->array_origin;
        delete arr;
    }
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    if (index < arr->size) {
        return arr->array_origin[index];
    }
    else return (Data)0;
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if(index < arr->size) {
        arr->array_origin[index] = value;
    }
    else std::cerr << "Error index" << std::endl;
}

// returns array size
size_t array_size(const Array *arr)
{ 
    return arr ? arr->size : 0;
}
