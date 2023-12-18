#include "array.h"

struct Array
{
    Data* data;  // Используем указатель на Data вместо самого Data
    size_t size;
};

// Создание массива
Array array_create(size_t size)
{
    Array newArr;
    newArr.data = new Data[size];
    newArr.size = size;
    return newArr;
}

// Удаление массива, освобождение памяти
void array_delete(Array arr)
{
    delete[] arr.data;
}

// Возвращает указанный элемент массива
Data array_get(const Array arr, size_t index)
{
    if (index < arr.size) {
        return arr.data[index];
    }
    else {
        // Обработка ошибки выхода за границы массива
        return Data(); // Возвращаем значение по умолчанию для типа Data
    }
}

// Устанавливает значение указанного элемента массива
void array_set(Array arr, size_t index, Data value)
{
    if (index < arr.size) {
        arr.data[index] = value;
    }
    else {
        // Обработка ошибки выхода за границы массива
    }
}

// Возвращает размер массива
size_t array_size(const Array arr)
{
    return arr.size;
}
