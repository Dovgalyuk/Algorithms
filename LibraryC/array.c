#include "array.h"

typedef struct Array
{
    size_t size;      
    Data* elements;   
    FFree* free_func;

} Array;

// create array
Array* array_create(size_t size, FFree* free_func)
{
    Array* arr = (Array*) malloc(sizeof(Array)); 
    if (arr == NULL)
        return NULL; 

    arr->size = size;
    arr->elements = (Data*)malloc(sizeof(Data) * size); 
    if (arr->elements == NULL)
    {
        free(arr);   
        return NULL;
    }

    arr->free_func = free_func;
    return arr;
}

// delete array, free memory
void array_delete(Array* arr)
{
    if (arr != NULL)
    {
        if (arr->free_func != NULL)
        {
            for (size_t i = 0; i < arr->size; i++)
            {
                arr->free_func((void*)arr->elements[i]);
            }
        }
        free(arr->elements); 
        free(arr);           
    }
}

// returns specified array element
Data array_get(const Array* arr, size_t index)
{
    return (Data) arr->elements[index];
}

// sets the specified array element to the value
void array_set(Array* arr, size_t index, Data value)
{
    if (index < arr->size)
    {
        arr->elements[index] = value;
    }
    
}

// returns array size
size_t array_size(const Array *arr)
{
    return (size_t)(arr->size);
}
