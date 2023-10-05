#include "vector.h"

struct Vector
{
    size_t size;
    size_t max_size;
    Data* data;
    Vector(){
        this->size = 0;
        this->max_size = 1;
        this->data = new Data[max_size];
    }
    ~Vector(){
        delete[] this->data;
    }
};

Vector* vector_create()
{
    return new Vector();
}

void vector_delete(Vector* vector)
{
    // TODO: free vector internals
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
    return vector->size;
}

void vector_resize(Vector* vector, size_t size)
{
    if (size <= vector->max_size) {
        vector->size = size;
        return;
    }
    vector->max_size = size * 2;
    Data* new_data = new Data[vector->max_size];
    for (size_t i = 0; i < vector->size; i++) {
        new_data[i] = vector->data[i];
    }
    delete[] vector->data;
    vector->size = size;
    vector->data = new_data;
}
