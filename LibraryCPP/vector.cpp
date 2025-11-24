#include "vector.h"

struct Vector
{
    Data* data;
    size_t size;
    size_t capacity;
};

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
    delete[] vector->data;
    delete vector;
}

Data vector_get(const Vector* vector, size_t index)
{
    if (index < vector->size) {
        return vector->data[index];
    }
    return 0;
}

void vector_set(Vector* vector, size_t index, Data value)
{
    if (index < vector->size) {
        vector->data[index] = value;
    }
}

size_t vector_size(const Vector* vector)
{
    return vector->size;
}

void vector_resize(Vector* vector, size_t new_size)
{
    if (new_size <= vector->capacity) {
        vector->size = new_size;
        return;
    }

    size_t new_capacity = (vector->capacity == 0) ? 1 : vector->capacity * 2;
    if (new_capacity < new_size) {
        new_capacity = new_size;
    }

    Data* new_data = new Data[new_capacity];

    for (size_t i = 0; i < vector->size; i++) {
        new_data[i] = vector->data[i];
    }

    for (size_t i = vector->size; i < new_size; i++) {
        new_data[i] = 0;
    }

    delete[] vector->data;
    vector->data = new_data;
    vector->size = new_size;
    vector->capacity = new_capacity;
}