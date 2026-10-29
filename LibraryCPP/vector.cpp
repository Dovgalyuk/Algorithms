#include "vector.h"

#include <algorithm>
#include <stdexcept>

struct Vector
{
    Data* elements;
    size_t size;
    size_t capacity;
};

Vector* vector_create()
{
    return new Vector{nullptr, 0, 0};
}

void vector_delete(Vector* vector)
{
    if (vector == nullptr)
        return;

    delete[] vector->elements;
    delete vector;
}

Data vector_get(const Vector* vector, size_t index)
{
    if (vector == nullptr)
        throw std::invalid_argument("be me");

    if (index >= vector->size)
        throw std::out_of_range("ni be ni me");

    return vector->elements[index];
}

void vector_set(Vector* vector, size_t index, Data value)
{
    if (vector == nullptr)
        throw std::invalid_argument("che dum");

    if (index >= vector->size)
        throw std::out_of_range("a tut che dum");

    vector->elements[index] = value;
}

size_t vector_size(const Vector* vector)
{
    if (vector == nullptr)
        throw std::invalid_argument("ne");

    return vector->size;
}

void vector_resize(Vector* vector, size_t size)
{
    if (vector == nullptr)
        throw std::invalid_argument("ne");

    if (size > vector->capacity)
    {
        size_t new_capacity = std::max(size,vector->capacity == 0 ? size_t{1} : vector->capacity * 2);

        Data* new_elements = new Data[new_capacity];

        if (vector->size > 0)
        {
            std::copy(vector->elements, vector->elements + vector->size, new_elements);
        }

        delete[] vector->elements;

        vector->elements = new_elements;
        vector->capacity = new_capacity;
    }

    if (size > vector->size)
    {
        std::fill(vector->elements + vector->size, vector->elements + size, Data{});
    }

    vector->size = size;
}