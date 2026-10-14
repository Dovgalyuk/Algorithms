#include "vector.h"

struct Vector
{
    Data* data;
    size_t size;
    size_t capacity;
};

Vector *vector_create()
{
    Vector* vector = new Vector;
    vector->size = 0;
    vector->data = nullptr;
    vector->capacity = 0;
    return vector;
}

void vector_delete(Vector *vector)
{
    // TODO: free vector internals
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

void vector_resize(Vector* vector, size_t size)
{
    if (size <= vector->capacity) {
        for (size_t i = vector->size; i < size; i++) {
            vector->data[i] = 0;
        }

        vector->size = size;
        return;
    }
    
    size_t newCapacity = vector->capacity;

    if (newCapacity == 0) {
        newCapacity = 1;
    }

    while (newCapacity < size) {
        newCapacity *= 2;
    }

    Data* newData = new Data[newCapacity]{};

    for (size_t i = 0; i < vector->size; i++) {
        newData[i] = vector->data[i];
    }

    delete[] vector->data;

    vector->data = newData;
    vector->size = size;
    vector->capacity = newCapacity;
}