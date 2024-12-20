#include "vector.h"

struct Vector
{
    Data * dt;
    size_t sz;
};

Vector *vector_create()
{
    Vector * nv = new Vector();
    nv->sz=100;
    nv->dt = new Data[nv->sz];
    return nv;
}

void vector_delete(Vector *vector)
{
    delete vector->dt;
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
    return vector->sz;
}

void vector_resize(Vector *vector, size_t size)
{
    Data * ndt = new Data[size];
    for (int i = 0; i<vector->sz;i++){
        ndt[i] = vector->dt[i];
    }
    delete vector->dt;
    vector->dt = ndt;
}
