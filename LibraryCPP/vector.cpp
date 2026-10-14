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
    if (vector == nullptr)
        return;
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
    if (vector->capacity < size) {
        size_t new_capacity = (vector->capacity == 0) ? 1 : vector->capacity;
        while (new_capacity < size)
            new_capacity *= 2;

        Data *new_data = new Data[new_capacity];

        for (size_t i = 0; i < vector->size && i < new_capacity; ++i)
            new_data[i] = vector->data[i];

        for (size_t i = vector->size; i < new_capacity; ++i)
            new_data[i] = (Data)0;

        delete[] vector->data;
        vector->data = new_data;
        vector->capacity = new_capacity;
    }
    else if (vector->capacity > size) {
        for (size_t i = vector->size; i < size; ++i)
            vector->data[i] = (Data)0;
    }
    vector->size = size;
}