#include "vector.h"

struct Vector
{
    size_t size;
    size_t capacity;
    Data* data;
    Vector()
    {
        size = 0;
        capacity = 0;
        data = nullptr;
    }
   
};

Vector *vector_create()
{
    return new Vector;
}

void vector_delete(Vector *vector)
{
    delete[] vector->data;
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
        if (vector->capacity == 0)
            vector->capacity = 1;
        while (vector->capacity < size)
            vector->capacity *= 2;
        Data* new_ptr = new Data[vector->capacity];
        for (size_t i = 0; i < vector->size; i++)
            new_ptr[i] = vector_get(vector, i);
        delete[] vector->data;
        vector->data = new_ptr;
        vector->size = size;
    }
    else
        vector->size = size;
}
