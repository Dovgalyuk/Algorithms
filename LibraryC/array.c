#include <stdlib.h>
#include "array.h"

typedef struct Array
{
    size_t size;
    Data value;
} Array;

// create array
Array *array_create(size_t size, FFree f)
{
    Array *result = malloc(sizeof(Array));
    if (result == NULL) {
        return NULL;
    }
    result->size = size;
    return result;
}

// delete array, free memory
void array_delete(Array *arr)
{
    free(arr);
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    return arr[index].value;
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    arr[index].value = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->size;
}
