#include <stdexcept>
#include "vector.h"
#include <algorithm>

struct Vector
{
    size_t capacity;
    size_t size;
    Data* element;
};

Vector* vector_create()
{
    Vector* vector = new Vector;
    vector->capacity = 10;
    vector->size = 0;
    vector->element = new Data[vector->capacity];
    return vector;
}

void vector_delete(Vector* vector)
{
    delete[] vector->element;
    delete vector;
}

Data vector_get(const Vector* vector, size_t index)
{
    if (index >= vector->size)
        throw std::out_of_range("ERROR of range");
    return vector->element[index];
}

void vector_set(Vector* vector, size_t index, Data value)
{
    if (index >= vector->size)
        throw std::out_of_range("ERROR of range");

    vector->element[index] = value;
}

size_t vector_size(const Vector* vector)
{
    return vector->size;
}

void vector_resize(Vector* vector, size_t new_size)
{
    if (new_size > vector->capacity) {
        while (new_size > vector->capacity) {
            vector->capacity *= 2;
        }
        Data* new_data = new Data[vector->capacity];
        std::copy(vector->element, vector->element + vector->size, new_data);
        delete[] vector->element;
        vector->element = new_data;
    }
    vector->size = new_size;
}