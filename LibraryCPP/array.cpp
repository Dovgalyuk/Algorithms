#include "array.h"

struct Array
{
    Data* m_data;
    size_t m_size;
};

// create array
Array *array_create(size_t size)
{
    Array* arr = new Array;
    arr->m_size = size;
    arr-> m_data = new Data[size];
    return arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    if (arr)
    {
        delete[] arr->m_data;
        delete arr;
    }
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{   
    if (index < arr->m_size)
    {
        return arr->m_data[index];
    }
    return (Data)0;
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (index < arr->m_size)
    {
        arr->m_data[index] = value;
    }
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr ? arr->m_size : 0;
}
