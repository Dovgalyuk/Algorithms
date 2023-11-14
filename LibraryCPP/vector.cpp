#include "vector.h"

struct Vector
{
    Data* data;
    size_t size;

    Vector()
    {
        size = 0;
        data = new Data[size_t(1)];
    }

    ~Vector()
    {
        delete[] data;
    }
};

Vector *vector_create()
{
    return new Vector;
}

void vector_delete(Vector *vector)
{
    // TODO: free vector internals
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    size_t size = vector->size;
    if (size <= index)
    {
        throw "Error";
    }

    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    size_t size = vector->size;
    if (size <= index)
    {
        throw "Error";
    }
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    Data* tmp = new Data[size];

    size_t k;

    if (size > vector->size) k = vector->size;
    else k = size;

    for (size_t i = 0; i < k; i++)
    {
        tmp[i] = vector_get(vector, i);
    }

    delete[] vector->data;

    vector->data = tmp;

    vector->size = size;
}
