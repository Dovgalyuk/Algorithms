#include "vector.h"

struct Vector
{
    Data  *data;
    size_t size;
    size_t capacity;
};

Vector *vector_create()
{
    Vector *v = new Vector;
    v->data = nullptr;
    v->size = 0;
    v->capacity = 0;
    return v;
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
    if (size > vector->capacity)
    {
        size_t newCap = (vector->capacity == 0) ? 1 : vector->capacity;
        while (newCap < size) newCap *= 2;
        Data *newData = new Data[newCap];
        for (size_t i = 0; i < vector->size; ++i)
            newData[i] = vector->data[i];
        for (size_t i = vector->size; i < newCap; ++i)
            newData[i] = 0;
        delete[] vector->data;
        vector->data = newData;
        vector->capacity = newCap;
    }
    vector->size = size;
}
