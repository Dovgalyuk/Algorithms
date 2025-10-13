#include "array.h"

struct Array
{
    Data* data;
    size_t size;
};

// create array  - создание массива
Array *array_create(size_t size)
{
    Array* array = new Array;
    array->data = new Data[size];
    array->size = size;

    return array;
}

// delete array, free memory - удаление массива, очищение памяти
void array_delete(Array *arr)
{
    delete[] arr->data;
    delete arr;
}

// returns specified array element - возвращение указанного элемента массива
Data array_get(const Array *arr, size_t index)
{
    if (index >= arr->size){
        return (Data)0;
    }

    return arr->data[index];
}

// sets the specified array element to the value - присваивание указанному элементу массива значение
void array_set(Array *arr, size_t index, Data value)
{
    if (index >= arr->size){
        return;
    }

    arr->data[index] = value; 

}

// returns array size - возвращение размера массива
size_t array_size(const Array *arr)
{
    return arr->size;
    
}
