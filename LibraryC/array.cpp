#include "array.h"
#include <stdlib.h>

struct Array {
    Data* data; 
    size_t size;   
    FFree* free_func; 
};

// create array
Array* array_create(size_t size, FFree f)
{
    Array* arr = (Array*)malloc(sizeof(Array)); 
    arr->data = (Data*)malloc(size * sizeof(Data));
    arr->size = size;
    arr->free_func = f;
    return arr;
}

// delete array, free memory
void array_delete(Array* arr)
{
    if (arr)
    {
        if (arr->free_func)
        {
            for (size_t i = 0; i < arr->size; i++)
                arr->free_func((void*)arr->data[i]);
        }
        free(arr->data);
        free(arr);
    }
}

// returns specified array element
Data array_get(const Array* arr, size_t index)
{
    if (index >= arr->size) return 0;
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array* arr, size_t index, Data value)
{
    if (index < arr->size)
        arr->data[index] = value;
}

// returns array size
size_t array_size(const Array* arr)
{
    return arr->size;
}