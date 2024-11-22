#include "vector.h"
#include <algorithm>

struct Vector
{
    Data* data;
    size_t size;
    size_t capacity;
};

Vector *vector_create()
{
    Vector *vector = new Vector;
    vector->size = 0;
    vector->capacity = 1;
    vector->data = new Data[vector->capacity];
    return vector;
}

void vector_delete(Vector *vector)
{
    delete[] vector->data;
    delete vector;
}

Data vector_get(const Vector *vector, size_t index)
{
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size > vector->capacity) {
        while (vector->capacity < size) {
            vector->capacity *= 2;
        }
        Data *new_data = new Data[vector->capacity];
        std::copy(vector->data, vector->data + vector->size, new_data);
        delete[] vector->data;
        vector->data = new_data;
    }
    vector->size = size;
}