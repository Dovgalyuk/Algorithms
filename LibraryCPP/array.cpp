#include "array.h"
#include <cstdlib>

struct Array
{
    Data* data;      
    size_t size;    
};

// create array
Array* array_create(size_t size)
{
    Array* arr = new Array;
    arr->data = new Data[size];  
    arr->size = size;           
    return arr;
}

// delete array, free memory
void array_delete(Array* arr)
{
    delete[] arr->data;  // освобождаем память данных
    delete arr;          // освобождаем память структуры
}

// returns specified array element
Data array_get(const Array* arr, size_t index)
{
    if (index >= arr->size)
        return (Data)0;  // возвращаем 0 если индекс вне диапазона
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array* arr, size_t index, Data value)
{
    if (index >= arr->size)
        return;  // выходим если индекс вне диапазона
    arr->data[index] = value;
}

// returns array size
size_t array_size(const Array* arr)
{
    return arr->size;
}