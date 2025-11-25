#include "vector.h"

struct Vector
{
    Data*  data;
    size_t size;
    size_t capacity;
};

Vector *vector_create()
{
    Vector* v = new Vector;
    v->data = nullptr;
    v->size = 0;
    v->capacity = 0;
    return v;
}

void vector_delete(Vector *vector)
{
    if (!vector)
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
    return vector ? vector->size : 0;
}

void vector_resize(Vector *vector, size_t newSize)
{
    if (!vector)
        return;

    if (newSize <= vector->capacity)
    {
        vector->size = newSize;
        return;
    }

    size_t newCapacity = (vector->capacity == 0 ? 1 : vector->capacity);
    while (newCapacity < newSize)
        newCapacity *= 2;

    Data* newData = new Data[newCapacity];

    for (size_t i = 0; i < vector->size; ++i)
        newData[i] = vector->data[i];

    delete[] vector->data;

    vector->data     = newData;
    vector->capacity = newCapacity;
    vector->size     = newSize;
}