#include "vector.h"
#include <iostream>
#include <stdexcept>

struct Vector 
{
    Data *data;
    size_t size;
    size_t capacity;
};

Vector *vector_create()
{
    Vector* vector = new Vector;
    vector->size = 0;
    vector->capacity = 4;
    vector->data = new Data[vector->capacity];
    return vector;
}

void vector_delete(Vector *vector)
{
    delete[] vector->data; 
    delete vector;
}

Data vector_get(const Vector *vector, size_t index)
{
    if (index >= vector->size) {
        throw std::out_of_range("Index out of range");
    }
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index >= vector->size) {
        throw std::out_of_range("Index out of range");
    }
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size > vector->capacity) {
        size_t new_capacity = vector->capacity * 2;
        while (new_capacity < size) new_capacity *= 2;
        Data* new_data = new Data[new_capacity];
        for (size_t i = 0; i < vector->size; i++) {
            new_data[i] = vector->data[i];
        }
        for (size_t i = vector->size; i < size; i++) {
            new_data[i] = Data();
        }
        delete[] vector->data;
        vector->data = new_data;
        vector->capacity = new_capacity;
    }
    vector->size = size;
}
