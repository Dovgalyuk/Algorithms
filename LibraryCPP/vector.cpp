#include <stdexcept>
#include "vector.h"

struct Vector
{
    size_t capacity;
    size_t size;
    Data *element;
};

Vector *vector_create()
{
    Vector* vector = new Vector;
    vector->capacity = 10;
    vector->size = 0;
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
    if (vector->size <= index)
        throw std::out_of_range("ERROR of range");
    return vector->element[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (vector->size <= index)
        throw std::out_of_range("ERROR of range");

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
            vector->capacity *= 2;
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
void capacity_vector(Vector *vector, size_t capac) {
    vector->capacity = capac;
}
