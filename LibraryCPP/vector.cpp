#include "vector.h"
#include <algorithm>
#include <stdexcept>

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
    if (!vector) return;
    
    delete[] vector->data;
    delete vector;
}

Data vector_get(const Vector *vector, size_t index)
{
    if (!vector || !vector->data || index >= vector->size) {
        throw std::out_of_range("Index out of range");
    }
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (!vector || !vector->data || index >= vector->size) {
        throw std::out_of_range("Index out of range");
    }
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector ? vector->size : 0;
}

void vector_resize(Vector *vector, size_t size)
{
    if (!vector) return;

    if (size > vector->capacity) {
        size_t new_capacity = vector->capacity == 0 ? 1 : vector->capacity;
        while (new_capacity < size) {
            new_capacity *= 2;
        }
        
        Data* new_data = new Data[new_capacity];
        
        if (vector->data) {
            std::copy(vector->data, vector->data + vector->size, new_data);
            delete[] vector->data;
        }
        
        vector->data = new_data;
        vector->capacity = new_capacity;
    }
    
    vector->size = size;
}
