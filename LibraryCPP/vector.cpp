#include "vector.h"
#include <cstdlib>
#include <cstring>

struct Vector
{
    Data* data;
    size_t size;
    size_t capacity;
};

Vector *vector_create()
{
    Vector* vector = new Vector;
    vector->data = nullptr;
    vector->size = 0;
    vector->capacity = 0;
    return vector;
}

void vector_delete(Vector *vector)
{
    if (vector) {
        delete[] vector->data;
        delete vector;
    }
}

Data vector_get(const Vector *vector, size_t index)
{
    if (vector && index < vector->size) {
        return vector->data[index];
    }
    return 0;
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (vector && index < vector->size) {
        vector->data[index] = value;
    }
}

size_t vector_size(const Vector *vector)
{
    return vector ? vector->size : 0;
}

void vector_resize(Vector *vector, size_t size)
{
    if (!vector) return;

    if (size > vector->capacity) {
        size_t new_capacity = size * 2;
        Data* new_data = new Data[new_capacity];
        
        // Копируем существующие данные
        for (size_t i = 0; i < vector->size; ++i) {
            new_data[i] = vector->data[i];
        }
        
        // Инициализируем новые элементы нулями
        for (size_t i = vector->size; i < size; ++i) {
            new_data[i] = 0;
        }
        
        delete[] vector->data;
        vector->data = new_data;
        vector->capacity = new_capacity;
    }
    else if (size < vector->size) {
        // Просто уменьшаем размер, память не освобождаем
        for (size_t i = size; i < vector->size; ++i) {
            vector->data[i] = 0;
        }
    }
    else if (size > vector->size) {
        // Инициализируем новые элементы нулями
        for (size_t i = vector->size; i < size; ++i) {
            vector->data[i] = 0;
        }
    }
    
    vector->size = size;
}