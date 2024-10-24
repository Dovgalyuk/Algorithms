#include "vector.h"
#include <stdexcept>  // Для выброса исключений std::out_of_range

// Структура для представления вектора
struct Vector {
    Data* data;      // Массив данных
    size_t capacity; // Текущая емкость вектора
    size_t size;     // Текущий размер вектора
};

// Создание нового вектора
Vector* vector_create() {
    Vector* vector = new Vector;
    vector->size = 0;
    vector->capacity = 4; // Начальная емкость
    vector->data = new Data[vector->capacity];
    return vector;
}

// Удаление вектора и освобождение выделенной памяти
void vector_delete(Vector* vector) {
    delete[] vector->data; // Удаление данных
    delete vector;         // Удаление самой структуры
}

// Получение элемента по индексу
Data vector_get(const Vector* vector, size_t index) {
    if (index >= vector->size) {
        throw std::out_of_range("Index out of bounds"); // Выброс исключения при некорректном индексе
    }
    return vector->data[index];
}

// Установка значения элемента по индексу
void vector_set(Vector* vector, size_t index, Data value) {
    if (index >= vector->size) {
        throw std::out_of_range("Index out of bounds"); // Выброс исключения при некорректном индексе
    }
    vector->data[index] = value;
}

// Получение текущего размера вектора
size_t vector_size(const Vector* vector) {
    return vector->size;
}

// Изменение размера вектора
void vector_resize(Vector* vector, size_t new_size) {
    if (new_size > vector->capacity) {
        // Увеличиваем емкость, удваивая ее до тех пор, пока не будет достаточно
        while (vector->capacity < new_size) {
            vector->capacity *= 2;
        }
        // Выделяем новую память с увеличенной емкостью
        Data* new_data = new Data[vector->capacity];
        // Копируем старые данные в новый массив
        for (size_t i = 0; i < vector->size; ++i) {
            new_data[i] = vector->data[i];
        }
        // Освобождаем старый массив
        delete[] vector->data;
        // Устанавливаем указатель на новый массив
        vector->data = new_data;
    }
    vector->size = new_size; // Устанавливаем новый размер
}
