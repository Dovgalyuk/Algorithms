#include <stdlib.h>
#include "array.h"

typedef struct Array {
    // remove this
    size_t size;
    Data *data;
} Array;


// create array
Array* array_create(size_t size)
{
    Array* arr = malloc(sizeof(Array));
    if (!arr) return NULL;             

    arr->size = size;
    arr->data = malloc(size * sizeof(Data)); 
    if (!arr->data) {
        free(arr);
        printf("Данные в массив не введены");
        return NULL;
    }

    printf("Массив создан");
    return arr;
    
}

// delete array, free memory
void array_delete(Array* arr)
{
    if (arr) {
        free(arr->data); 
        free(arr); 
        printf("Память очищена");

    }

    
   
}

// returns specified array element
Data array_get(const Array* arr, size_t index)
{
    if(index < arr->size)
    {
        return arr->data[index];
    }

    return (Data)0
}

// sets the specified array element to the value
void array_set(Array* arr, size_t index, Data value)
{
     if(index < arr->size)
    {
        return arr->data[index] = value;
    }
}

// returns array size
size_t array_size(const Array* arr)
{

    if(arr)
    {
        return arr->size;
    }

    return 0;
   

}
