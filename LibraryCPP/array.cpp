#include "array.h"

struct Array
{
    Data* data;
    size_t size;
};

// create array
// выделение памяти под массив указанного размера
Array* array_create(size_t size)
{
    Array* arr = new Array;
    arr->size = size;
    arr->data = new Data[size](); // заполнение элементов массива нулями
    return arr;
}

// delete array, free memory
// освобождение выделенной памяти 
void array_delete(Array* arr)
{
    if (arr) {
        delete[] arr->data;
        delete arr;
    }
}

// returns specified array element
// возврат элемента массива
Data array_get(const Array* arr, size_t index)
{
    if (!arr || index >= arr->size) {
        return (Data)0;
    }
    return arr->data[index];
}

// sets the specified array element to the value
// присвоение значения
void array_set(Array* arr, size_t index, Data value)
{
    if (!arr || index >= arr->size) {
        return;
    }
    arr->data[index] = value;
}

// returns array size
// возврат размера массива
size_t array_size(const Array* arr)
{
    return arr ? arr->size : 0;
}

