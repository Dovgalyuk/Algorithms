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
    ~Vector()
    {
        delete[] data;
        data = nullptr;
    }
};

Vector* vector_create()
{
    return new Vector;
}

void vector_delete(Vector* vector)
{
    delete vector;
}

Data vector_get(const Vector* vector, size_t index)
{
    return vector->data[index];
}

void vector_set(Vector* vector, size_t index, Data value)
{
    vector->data[index] = value;
}

size_t vector_size(const Vector* vector)
{
    return vector->size;
}

void vector_resize(Vector* vector, size_t size)
{
    if (size > vector->capacity) {
        if (vector->capacity == 0)
            vector->capacity = 1;
        while (vector->capacity < size)
            vector->capacity *= 2;
        int* ptr = new int[vector->capacity];
        for (int i = 0; i < vector->size; i++)
            ptr[i] = vector->data[i];
        vector->size = size;
        delete[] vector->data;
        vector->data = ptr;
    }
    else
        vector->size = size;
}