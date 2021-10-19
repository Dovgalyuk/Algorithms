#include "vector.h"
struct Vector
{
    Data* data;
    size_t size;
    size_t capacity;
    Vector() {
        size = 0;
        capacity = 0;
        data = nullptr;
    }
    ~Vector() {
        delete data;
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
    
    if (size <= vector->capacity) {
        vector->size = size;
    } else {
        if (vector->capacity == 0) 
            vector->capacity = 1;
        while (vector->capacity < size) {
            vector->capacity *= 2;
        }
        Data* newData = new Data[vector->capacity];
        for (size_t i = 0; i < vector->size; i++) {
            newData[i] = vector_get(vector, i);
        }
        delete[] vector->data;
        vector->data = newData;
        vector->size = size;
    }
    
}
