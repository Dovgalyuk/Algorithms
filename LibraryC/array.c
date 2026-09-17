#include "array.h"
#include <stdlib.h>

struct Array {
    Data *data;
    size_t size;
    FFree *free_value;
};

// create array
Array *array_create(size_t size, FFree f)
{
    Array *arr = malloc(sizeof(*arr));
    if (arr == NULL)
        return NULL;

    arr->data = NULL;
    arr->size = size;
    arr->free_value = f;

    if (size != 0)
    {
        arr->data = calloc(size, sizeof(*arr->data));
        if (arr->data == NULL)
        {
            free(arr);
            return NULL;
        }
    }

    return arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    if (arr == NULL)
        return;

    if (arr->free_value != NULL)
    {
        for (size_t i = 0; i < arr->size; ++i)
        {
            if (arr->data[i] != (Data)0)
                arr->free_value((void *)arr->data[i]);
        }
    }

    free(arr->data);
    free(arr);
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    if (arr == NULL || index >= arr->size)
        return (Data)0;

    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (arr == NULL || index >= arr->size)
        return;

    if (arr->free_value != NULL && arr->data[index] != (Data)0
        && arr->data[index] != value)
    {
        arr->free_value((void *)arr->data[index]);
    }

    arr->data[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr == NULL ? 0 : arr->size;
}
