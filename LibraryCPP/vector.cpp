#include "vector.h"

struct Vector
{
    Data* adr;
    size_t n;
    size_t v;
};

Vector *vector_create()
{
    Vector* vector = new Vector;
    vector->adr = nullptr;
    vector->n = 0;
    vector->v = 0;
    return vector;
}

void vector_delete(Vector *vector)
{
    delete[] vector->adr;
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    if (index < vector->n) {
        return vector->adr[index];
    }
    return (Data)0;
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index < vector->n) {
        vector->adr[index] = value;
    }
}

size_t vector_size(const Vector *vector)
{
    return vector->n;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size <= vector->v) {
        vector->n = size;
    }
    else
    {
        size_t newv = size * 2;
        Data* newadr = new Data[newv];
        for (size_t i = 0; i < vector->n; i++)
        {
            newadr[i] = vector->adr[i];
        }
        for (size_t i = vector->n; i < size; i++)
        {
            newadr[i] = (Data)0;
        }
        delete[] vector->adr;
        vector->adr = newadr;
        vector->n = size;
        vector->v = newv;
    }
}
