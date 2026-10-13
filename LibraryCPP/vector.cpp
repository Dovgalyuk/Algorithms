#include "vector.h"

struct Vector
{
    int *Data;
    size_t maxCapacity;
    size_t currLength;
};

Vector *vector_create()
{
    Vector* vector = new Vector;
    vector->maxCapacity = 4;
    vector->currLength = 0;
    vector->Data = new Data[vector->maxCapacity];
    return vector;
}

void vector_delete(Vector *vector)
{
    if (vector) {
        delete[] vector->Data;
        delete vector;
    }
}

Data vector_get(const Vector *vector, size_t index)
{
    if (index < vector->currLength) {
        return vector->Data[index];
    }
    return (Data)0;
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index < vector->currLength) {
        vector->Data[index] = value;
    }
}

size_t vector_size(const Vector *vector)
{
    return vector->currLength;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size > vector->maxCapacity) {
        size_t newCapacity = vector->maxCapacity * 2;
        while (newCapacity < size) {
            newCapacity *= 2;
        };

        Data* new_data = new Data[newCapacity];
        for (size_t i = 0; i < vector->currLength; ++i) {
            new_data[i] = vector->Data[i];
        }
        delete[] vector->Data;
        vector->Data = new_data;
        vector->maxCapacity = newCapacity;
    }
    vector->currLength = size;
}