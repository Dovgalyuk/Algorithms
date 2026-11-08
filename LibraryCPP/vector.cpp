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
    if (vector == nullptr)
        return;

    delete[] vector->data;
    delete vector;
}

Data vector_get(const Vector* vector, size_t index)
{
    if (vector == nullptr || index >= vector->size)
        return Data{};

    return vector->data[index];
}

void vector_set(Vector* vector, size_t index, Data value)
{
    if (vector == nullptr || index >= vector->size)
        return;

    vector->data[index] = value;
}

size_t vector_size(const Vector* vector)
{
    if (vector == nullptr)
        return 0;

    return vector->size;
}

void vector_resize(Vector* vector, size_t size)
{
    if (vector == nullptr)
        return;

    if (size > vector->capacity)
    {
        size_t newCapacity = vector->capacity == 0
            ? 1
            : vector->capacity;

        while (newCapacity < size)
            newCapacity *= 2;

        Data* newData = new Data[newCapacity]{};

        for (size_t i = 0; i < vector->size; ++i)
            newData[i] = vector->data[i];

        delete[] vector->data;

        vector->data = newData;
        vector->capacity = newCapacity;
    }

    if (size > vector->size)
    {
        for (size_t i = vector->size; i < size; ++i)
            vector->data[i] = Data{};
    }

    vector->size = size;
}
