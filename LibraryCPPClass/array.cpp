#include "array.h" // Подключаем заголовочный файл, где описаны функции работы с массивом
#include <stdexcept> // Подключаем библиотеку для работы с исключениями, такими как std::out_of_range

// Определение типа Data (например, int или структура)
typedef int Data; // Пример использования типа int

// Определение структуры Array
struct Array {
    Data* array; // Указатель на массив элементов типа Data
    size_t size; // Размер массива
};

// Функция для создания массива
Array* array_create(size_t size) {
    if (size == 0) { // Проверяем, что размер массива больше 0
        return nullptr; // Если размер 0, возвращаем null-указатель
    }
    Array* arr = new Array; // Выделяем память под структуру Array
    arr->size = size; // Устанавливаем размер массива
    arr->array = new Data[size]; // Выделяем память под массив элементов
    return arr; // Возвращаем указатель на созданный массив
}

// Функция для удаления массива и освобождения памяти
void array_delete(Array* arr) {
    if (arr) { // Проверяем, что указатель на массив не null
        delete[] arr->array; // Освобождаем память, выделенную под массив элементов
        delete arr; // Освобождаем память, выделенную под структуру Array
    }
}

// Функция для получения элемента массива по индексу
Data array_get(const Array* arr, size_t index) {
    if (!arr || index >= arr->size) { // Проверяем, что массив существует и индекс в пределах допустимого
        throw std::out_of_range("Index out of bounds"); // Если условие нарушено, выбрасываем исключение
    }
    return arr->array[index]; // Возвращаем элемент массива по указанному индексу
}

// Функция для установки значения элемента массива по индексу
void array_set(Array* arr, size_t index, Data value) {
    if (!arr || index >= arr->size) { // Проверяем, что массив существует и индекс в пределах допустимого
        throw std::out_of_range("Index out of bounds"); // Если условие нарушено, выбрасываем исключение
    }
    arr->array[index] = value; // Устанавливаем значение элемента массива
}

// Функция для получения размера массива
size_t array_size(const Array* arr) {
    if (!arr) { // Проверяем, что массив существует
        throw std::invalid_argument("Array is null"); // Если массив пуст, выбрасываем исключение
    }
    return arr->size; // Возвращаем размер массива
}
