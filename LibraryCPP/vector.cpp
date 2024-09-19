#include "vector.h"
#include <new>
#include <stdexcept>


struct Vector
{
    size_t size = 0;
    Data *pointer = nullptr;
};

Vector *vector_create()
{
    return new Vector;
}

void vector_delete(Vector *vector)
{
    if (!vector) throw std::invalid_argument("The vector pointer is null");

    if (vector->pointer) free(vector->pointer);
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    if (!vector) throw std::invalid_argument("The vector pointer is null");
    if (vector->size <= index) throw std::out_of_range("The index is out of range");
    
    return vector->pointer[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (!vector) throw std::invalid_argument("The vector pointer is null");
    if (vector->size <= index) throw std::out_of_range("The index is out of range");
    
    vector->pointer[index] = value;
}

size_t vector_size(const Vector *vector)
{
    if (!vector) throw std::invalid_argument("The vector pointer is null");

    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    Data *ptr;

    if (!vector) throw std::invalid_argument("The vector pointer is null");

    if (vector->pointer)
        ptr = (Data*)realloc(vector->pointer, sizeof(Data) * size);
    else
        ptr = (Data*)malloc(sizeof(Data) * size);
        
    if (!ptr) throw std::bad_alloc();
    vector->pointer = ptr;
    vector->size = size;
}

