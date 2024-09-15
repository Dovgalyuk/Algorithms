#include <stdlib.h>
#include "array.h"

typedef struct Array
{
    size_t size;
    Data* elem_ptr;

} Array;

// create array
Array *array_create(size_t size, FFree f)
{
    Array* ptr = malloc(sizeof(Array));
    ptr->size = size;
    ptr->elem_ptr = malloc(sizeof(Data)*size);
    return ptr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    free(arr->elem_ptr);
    free(arr);
}

// returns specified array element
Data* array_get(const Array *arr, size_t index)
{
    return (Data*) arr->elem_ptr + index;
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    *(arr->elem_ptr + index) = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return (size_t)(arr->size);
}
