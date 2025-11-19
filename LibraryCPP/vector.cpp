#include "vector.h"
#include <algorithm>
#include <stdexcept>

Vector* vector_create()
{
    Vector* vector = new Vector;
    vector->data = nullptr;
    vector->size = 0;
    vector->capacity = 0;
    return vector;
}

void vector_delete(Vector* vector)
{
    if (vector) {
        delete[] vector->data;
        delete vector;
    }
}

Data vector_get(const Vector* vector, size_t index)
{
    if (!vector || index >= vector->size) {
        throw std::out_of_range("Index out of range");
    }
    return vector->data[index];
}

void vector_set(Vector* vector, size_t index, Data value)
{
    if (!vector || index >= vector->size) {
        throw std::out_of_range("Index out of range");
    }
    vector->data[index] = value;
}

size_t vector_size(const Vector* vector)
{
    return vector ? vector->size : 0;
}

void vector_resize(Vector* vector, size_t size)
{
    if (!vector) return;
    
    if (size > vector->capacity) {
        size_t new_capacity = std::max(size, vector->capacity * 2);
        if (new_capacity == 0) new_capacity = 1;
        
        Data* new_data = new Data[new_capacity];
        
        for (size_t i = 0; i < vector->size; ++i) {
            new_data[i] = vector->data[i];
        }
        
        delete[] vector->data;
        vector->data = new_data;
        vector->capacity = new_capacity;
    }
    
    vector->size = size;
}