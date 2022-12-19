#include "array.h"

struct Array
{
    // У струтуры есть динамический массив и размер
    size_t number;
    Data* data;
    //Конструктор, получает размер, создаёт массив
    Array(size_t size)
    {
        number = size;
        data = new Data[size];
    }
};

// Функция создаёт струстуру, в ней просто возврщаем новый Array, создав его с конструктором
Array* array_create(size_t size)
{
    return new Array(size);
}

// Процедура удаляет структура, в ней удаляем динамический массив, чтобы освободить память в куче
void array_delete(Array* arr) 
{ 
    delete[] arr->data; 
    delete arr; 
}

// Функция возвращает элемент в заданой структуре, в заданом месте
Data array_get(const Array* arr, size_t index)
{
    // в случае, если заданный индекс больше, чем размер массива, возвращаем ноль
    if (index >= array_size(arr))
        return 0;
    else
        return (arr->data[index]);
}

// Процедура присвает заданному месту в заданой структуре, заданные данные
void array_set(Array* arr, size_t index, Data value)
{
    // в случае, если заданный индекс больше, чем размер массива, возвращаем ноль
    if (index >= array_size(arr))
        return;
    else
        arr->data[index] = value;
}

// Функция возвращает размер массива
size_t array_size(const Array* arr)
{
    return arr->number;
}
