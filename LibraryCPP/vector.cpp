#include "vector.h"

struct Vector
{
    Data *data;
    size_t size;
    size_t capacity;
};

Vector *vector_create()
{
    Vector *vector = new Vector;
    vector->data = nullptr;
    vector->size = 0;
    vector->capacity = 0;
    return vector;
}

void vector_delete(Vector *vector)
{
    if (vector == nullptr) {
        return;
    }
    delete[] vector->data;
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    if (index >= vector->size) {
        return (Data)-1; // Return a sentinel value for out-of-bounds access
    }
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index >= vector->size) {
        return;
    }
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size > vector->capacity) {
        size_t new_capacity = vector->capacity * 2;
        if (new_capacity < size) {
            new_capacity = size;
        }

        Data *new_data = new Data[new_capacity];
        for (size_t i = 0; i < vector->size; i++) {
            new_data[i] = vector->data[i];
        }
        delete[] vector->data;

        vector->data = new_data;
        vector->capacity = new_capacity;
    }
    for (size_t i = vector->size; i < size; i++) {
        vector->data[i] = (Data)0;
    }
    vector->size = size;
}
