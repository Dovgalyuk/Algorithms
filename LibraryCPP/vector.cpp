#include "vector.h"

struct Vector
{
    size_t dlina;
    size_t vmestimost;
    Data* data;
    Vector() : dlina(0), vmestimost(0), data(nullptr) {}
};

Vector* vector_create()
{
    return new Vector;
}

void vector_delete(Vector* vector)
{
    // TODO: free vector internals
    delete[] vector->data;
    delete vector;
}

Data vector_get(const Vector* vector, size_t index)
{
    return vector->data[index];
}

void vector_set(Vector* vector, size_t index, Data value)
{
    vector->data[index] = value;
}

size_t vector_size(const Vector* vector)
{
    return vector->dlina;
}

void vector_resize(Vector* vector, size_t size)
{
    if (vector->vmestimost < size) {
        if (vector->vmestimost == 0) {
            vector->vmestimost = 1;
        }
        while (vector->vmestimost < size) {
            vector->vmestimost = vector->vmestimost * 2;
        }
        Data* newData = new Data[vector->vmestimost];
        for (int i = 0; i < vector_size(vector); i++) {
            newData[i] = vector->data[i];
        }
        delete[] vector->data;
        vector->data = newData;
        vector->dlina = size;
    }
    else {
        vector->dlina = size;
    }
}