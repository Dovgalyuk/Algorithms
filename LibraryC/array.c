#include <stdlib.h>
#include "array.h"

typedef struct Array
{
    size_t size;
    Data* elem_ptr;
    FFree* destruct;

} Array;

// create array
Array *array_create(size_t size, FFree *f)
{
    Array* ptr = malloc(sizeof(Array));
    ptr->size = size;
    ptr->elem_ptr = (Data*) malloc(sizeof(Data) * size);
    ptr->destruct = f;
    return ptr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    if (arr->destruct != NULL)
    {
        for (size_t i = 0; i < array_size(arr); i++)
        {
            arr->destruct((void*)arr->elem_ptr[i]);
        }
    }
    free(arr->elem_ptr);
    free(arr);
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    return (Data) arr->elem_ptr[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    arr->elem_ptr[index] = value;

}

// returns array size
size_t array_size(const Array *arr)
{
    return (size_t)(arr->size);
}
