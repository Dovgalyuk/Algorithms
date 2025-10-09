#include "vector.h"

struct Vector
{
    Data* d;
    size_t size;
    size_t cap;
};

Vector *vector_create()
{
    Vector* vector = new Vector;
    vector->size = 0;
    vector->cap = 4;
    vector->d = new Data[vector->cap]{};
    return vector;
}

void vector_delete(Vector *vector)
{
    if(!vector) return;
    delete[] vector->d;
    delete vector;
}

Data vector_get(const Vector *vector, size_t index)
{
    if(!vector || index >= vector->size){
        return 0;
    }
    return vector->d[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if(!vector || index >= vector->size){
        return;
    }
    vector->d[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector ? vector->size : 0;
}

void vector_resize(Vector *vector, size_t size)
{
    if(!vector) return;

    if(size > vector->cap){
        size_t new_cap = vector->cap;
        while(new_cap < size) new_cap *= 2;
        Data* new_d = new Data[new_cap];

        for(size_t i = 0; i < vector->size; i++)
            new_d[i] = vector->d[i];
        
        delete[] vector->d;
        vector->d = new_d;
        vector->cap = new_cap;
    }
    vector->size = size;
}
