#include "vector.h"
#include <stdexcept>

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
    if (vector == nullptr) return;

    delete[] vector->data;
    delete vector;
}

Data vector_get(const Vector* vector, size_t index)
{
    if (index >= vector->size)
        throw std::out_of_range("vector index out of range");

    return vector->data[index];
}

void vector_set(Vector* vector, size_t index, Data value)
{
    if (index >= vector->size)
        throw std::out_of_range("vector index out of range");

    vector->data[index] = value;
}

size_t vector_size(const Vector* vector)
{
    return vector->size;
}

void vector_resize(Vector* vector, size_t size)
{
    if (size > vector->capacity)
    {
        size_t newCapacity = vector->capacity == 0 ? 1 : vector->capacity;

        while (newCapacity < size)
            newCapacity *= 2;

        Data* data = new Data[newCapacity];

        for (size_t i = 0; i < vector->size; ++i)
            data[i] = vector->data[i];

        delete[] vector->data;

        vector->data = data;
        vector->capacity = newCapacity;
    }

    vector->size = size;
}