#include "vector.h"

struct Vector
{
    Data * dt;
    size_t sz;
    size_t cap;
};

Vector *vector_create()
{
    Vector * nv = new Vector();
    nv->sz = 20;
    nv->cap = 20;
    nv->dt = new Data[nv->sz];
    return nv;
}

void vector_delete(Vector *vector)
{
    delete[] vector->dt;
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    return vector->dt[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    vector->dt[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->cap;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size <= vector->sz) {
        vector->cap = size;
    }
    else {
        Data* ndt = new Data[size * 2 + 1];
        for (size_t i = 0; i < vector->cap; i++) {
            ndt[i] = vector->dt[i];
        }
        delete vector->dt;
        vector->dt = ndt;
        vector->sz = size * 2 + 1;
        vector->cap = size;
    }
}
