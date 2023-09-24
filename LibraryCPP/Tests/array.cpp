#include "array.h"
#include <iostream>
using namespace std;


struct Array
{
public:
    Data* data;
    size_t sizeArr;


};

// create array
Array* array_create(size_t size)
{
    Array* arr = new Array;  //Выделение памяти под структуру
    arr->sizeArr = size;          //Выделение памяти под хранения размера массива
    arr->data = new Data[size];  // Выделения памяти под значения в массиве

    return arr;
}

// delete array, free memory
void array_delete(Array* arr)
{
    delete[] arr->data;   //Удаления массива
    delete arr;    //Удаление структуры
}

// returns specified array element
Data array_get(const Array* arr, size_t index)
{
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array* arr, size_t index, Data value)
{
    arr->data[index] = value;  //Присвоение значения в массив по заданному индексу


}

