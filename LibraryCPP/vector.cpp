#include "vector.h"

using namespace std;

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
    delete [] vector->data;
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

size_t vector_capacity(const Vector *vector)
{
    return vector->capacity;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size <= vector->capacity)
    {
        vector->size = size;
        return;
    }

    size_t newCapacity = vector->capacity > 0 ? vector->capacity * 2 : size;
    if (newCapacity < size)
        newCapacity = size;

    Data *newData = new Data[newCapacity];
    for (size_t i = 0; i < vector->size; i++)
        newData[i] = vector->data[i];

    delete[] vector->data;
    vector->data = newData;
    vector->capacity = newCapacity;
    vector->size = size;
}