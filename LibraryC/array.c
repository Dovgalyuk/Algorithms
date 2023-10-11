#include <stdlib.h>
#include "array.h"

typedef struct Array
{
    size_t size;
    Data *data;
} Array;

// create array
Array *array_create(size_t size, FFree f)
{
    Array *arr = (Array*)malloc(sizeof(Array));
    f(NULL);
    if (arr != NULL)
    {
        arr->data = (Data*)malloc(sizeof(Data) * size);
        arr->size = size;
    }
    return arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
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
    if (index < arr->size)
        arr->data[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->size;
}