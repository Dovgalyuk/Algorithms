#include "vector.h"

struct Vector
{
    Data* data;
    size_t size;
    size_t maxSize;
};

Vector *vector_create()
{
    Vector* vector = new Vector;
    vector->size = 0;
    vector->data = new Data[0];
    return vector;
}

void vector_delete(Vector *vector)
{
    delete[] vector->data;
    delete vector;
}

Data vector_get(const Vector *vector, size_t index)
{
    return vector -> data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index >=0 && index <= vector -> size) {
        vector->data[index] = value;
    }
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size < vector->maxSize) {
        vector->size = size;
    }
    else {
        size_t newSize = size * 2;
        Data* newVector = new Data[newSize];

        for (int i = 0; i < vector->size; i++) {
            newVector[i] = vector->data[i];
        }
        delete[] vector->data;

        vector->data = newVector;
        vector->size = size;
        vector->maxSize = newSize;
    }
}
