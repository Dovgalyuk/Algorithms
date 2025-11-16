#include "vector.h"
#include <algorithm>

Vector *vector_create()
{
    Vector *vector = new Vector;
    vector->arr = nullptr;
    vector->size = 0;
    vector->capacity = 0;
    return vector;
}

void vector_delete(Vector *vector)
{
    delete[] vector->arr;
    delete vector;
}

Data vector_get(const Vector *vector, size_t index)
{
    if (index >= vector->size) {
        throw std::out_of_range("Index out of range");
    }
    return vector->arr[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index >= vector->size) {
        vector_resize(vector, index + 1);
    }
    vector->arr[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size <= vector->capacity) {
        if (size > vector->size) {
            // Инициализируем новые элементы нулями
            for (size_t i = vector->size; i < size; i++) {
                vector->arr[i] = 0;
            }
        }
        vector->size = size;
        return;
    }

    // Нужно увеличить capacity
    size_t new_capacity = std::max(size, vector->capacity * 2);
    if (new_capacity == 0) new_capacity = 1;

    Data* new_data = new Data[new_capacity];
    
    // Копируем старые данные
    for (size_t i = 0; i < vector->size; i++) {
        new_data[i] = vector->arr[i];
    }
    
    // Инициализируем новые элементы нулями
    for (size_t i = vector->size; i < size; i++) {
        new_data[i] = 0;
    }

    delete[] vector->arr;
    vector->arr = new_data;
    vector->size = size;
    vector->capacity = new_capacity;
}