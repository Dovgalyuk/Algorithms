#include "vector.h"
#include <cstdlib>
#include <stdexcept>
#include <cstring>

struct Vector {
    Data* data;  // Указатель на динамически выделенный массив данных
    size_t size; // Количество элементов в векторе
    size_t capacity; // Вместимость вектора (сколько элементов может содержать)

    // Конструктор, инициализирующий поля структуры
    Vector() : data(nullptr), size(0), capacity(0) {}  // Инициализация полей
};

Vector* vector_create() {
    // Создание вектора с инициализацией
    Vector* vector = new Vector; // Здесь используется конструктор структуры
    return vector;
}

void vector_delete(Vector* vector) {
    delete[] vector->data;  // Освобождаем память, выделенную для данных
    delete vector;           // Освобождаем память для самого вектора
}

Data vector_get(const Vector* vector, size_t index) {
    if (index >= vector->size) {
        throw std::out_of_range("Index out of range");
    }
    return vector->data[index]; // Получаем элемент по индексу
}

void vector_set(Vector* vector, size_t index, Data value) {
    if (index >= vector->size) {
        throw std::out_of_range("Index out of range");
    }
    vector->data[index] = value; // Устанавливаем значение по индексу
}

size_t vector_size(const Vector* vector) {
    return vector->size;  // Возвращаем текущий размер вектора
}

void vector_resize(Vector* vector, size_t size) {
    // Если новый размер больше текущей емкости, увеличиваем размер
    if (size > vector->capacity) {
        size_t new_capacity = vector->capacity == 0 ? 1 : vector->capacity;
        while (new_capacity < size) {
            new_capacity *= 2; // Удваиваем емкость до тех пор, пока она не станет достаточной
        }

        // Выделяем новую память для данных
        Data* new_data = new Data[new_capacity];
        
        // Если старые данные существуют, копируем их в новый массив
        if (vector->data) {
            std::memcpy(new_data, vector->data, vector->size * sizeof(Data));
            delete[] vector->data; // Освобождаем старую память
        }

        vector->data = new_data;  // Указываем на новый массив
        vector->capacity = new_capacity;  // Обновляем емкость
    }

    vector->size = size;  // Устанавливаем новый размер
}
