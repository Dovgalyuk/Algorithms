#include <stdlib.h>
#include "array.h"

typedef struct Array {
    Data *data;
    size_t size;
    FFree *free_func;
} Array;

// create array
Array *array_create(size_t size, FFree f)
{
    Array *arr = (Array*)malloc(sizeof(Array));
    arr->size = size;
    arr->free_func = f;
    arr->data = size > 0 ? (Data*)calloc(size, sizeof(Data)) : NULL;
    return arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    if (arr->free_func)
    {
        size_t i;
        for (i = 0 ; i < arr->size ; ++i)
        {
            if (arr->data[i])
                arr->free_func((void*)arr->data[i]);
        }
    }
    free(arr->data);
    free(arr);
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    if (index >= arr->size)
        return (Data)0;
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (index >= arr->size)
        return;
    if (arr->free_func && arr->data[index])
        arr->free_func((void*)arr->data[index]);
    arr->data[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->size;
}
