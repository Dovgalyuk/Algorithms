#include "vector.h"
#include <algorithm> // для std::min

struct Vector
{
    Data* data;
    size_t size;
    size_t capacity;
    
    Vector() : data(nullptr), size(0), capacity(0) {}
};

Vector* vector_create()
{
    return new Vector;
}

void vector_delete(Vector* vector)
{
    delete[] vector->data;
    delete vector;
}

Data vector_get(const Vector* vector, size_t index)
{
    if (index >= vector->size) {
        return (Data)0; // или можно бросить исключение
    }
    return vector->data[index];
}

void vector_set(Vector* vector, size_t index, Data value)
{
    if (index >= vector->size) {
        return; // или можно бросить исключение
    }
    vector->data[index] = value;
}

size_t vector_size(const Vector* vector)
{
    return vector->size;
}

void vector_resize(Vector* vector, size_t new_size)
{
    if (new_size > vector->capacity) {
        // Увеличиваем capacity с коэффициентом 2
        size_t new_capacity = std::max(new_size, vector->capacity * 2);
        if (new_capacity < 4) new_capacity = 4;
        
        Data* new_data = new Data[new_capacity];
        
        // Копируем существующие данные
        for (size_t i = 0; i < vector->size; ++i) {
            new_data[i] = vector->data[i];
        }
        
        // Инициализируем новые элементы нулями
        for (size_t i = vector->size; i < new_capacity; ++i) {
            new_data[i] = (Data)0;
        }
        
        delete[] vector->data;
        vector->data = new_data;
        vector->capacity = new_capacity;
    }
    
    // Если уменьшаем размер, то просто меняем size
    vector->size = new_size;
}
