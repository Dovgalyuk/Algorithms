#include "vector.h"
#include <algorithm>
#include <limits>
#include <stdexcept>

struct Vector
{
    Data *data;
    size_t size;
    size_t capacity;
};

Vector *vector_create()
{
    Vector *myVector = new Vector;
    myVector->data = nullptr;
    myVector->size = 0;
    myVector->capacity = 0;

    return myVector;
}

void vector_delete(Vector *vector)
{
    delete[] vector->data;
    delete vector;
}

Data vector_get(const Vector *vector, size_t index)
{
    if (vector == nullptr)
    {
        throw std::invalid_argument("Vector is nullptr");
    }

    if (index >= vector->size)
    {
        throw std::out_of_range("Index out of range");
    }

    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (vector == nullptr || index >= vector->size)
        return;

    vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (vector == nullptr)
    {
        return;
    }

    if (size > vector->capacity)
    {
        size_t newCapacity = size;
        if (vector->capacity <= std::numeric_limits<size_t>::max() / 2)
            newCapacity = std::max(size, vector->capacity * 2);
        Data *newData = new Data[newCapacity];
    
        for (size_t i = 0; i < vector->size; i++)
        {
            newData[i] = vector->data[i];
        }
        
        delete[] vector->data;
        vector->data = newData;
        vector->capacity = newCapacity;
    }
    
    for (size_t i = vector->size; i < size; i++)
    {
        vector->data[i] = Data{};
    }

    vector->size = size;
}
