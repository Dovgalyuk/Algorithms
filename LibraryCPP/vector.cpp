#include "vector.h"
#include <stdexcept>
#define FACTOR 2                                        

struct Vector
{
    size_t capacity;
    size_t size;
    Data* element;
};

Vector *vector_create()
{
    Vector* vector = new Vector;
    vector->size = 0;
    vector->capacity = 10;
    vector->element = new Data[vector->capacity];
    return vector;
}

void vector_delete(Vector *vector)
{
    if (vector->element != nullptr) {
        delete[] vector->element;
    }

    delete vector;
}

Data vector_get(const Vector *vector, size_t index)
{
    if (vector->size <= index) {
        throw std::out_of_range("The index is out of range");
    }

    return vector->element[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (vector->size <= index) {
        throw std::out_of_range("The index is out of range");
    }

    vector->element[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size > vector->capacity) {
        while (vector->capacity < size) {
            vector->capacity *= FACTOR;
        }
        Data* new_data = new Data[vector->capacity];
        for (size_t i = 0; i < vector->size; ++i) {
            new_data[i] = vector->element[i];
        }
        delete[] vector->element;
        vector->element = new_data;
    }
    vector->size = size;
}
