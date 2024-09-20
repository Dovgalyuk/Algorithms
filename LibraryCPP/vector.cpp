#include "vector.h"
#include <new>
#include <cmath>
#include <stdexcept>

#define max(a, b) (((a) > (b)) ? (a) : (b))
#ifndef RESIZE_FACTOR
#define RESIZE_FACTOR 2
#endif

struct Vector
{
    size_t size = 0;
    size_t real_size = 0;
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

    if (vector->pointer){
        if (size > vector->real_size){
            size_t new_size = max(sizeof(Data)*size, sizeof(Data) * std::ceil(vector->real_size * RESIZE_FACTOR));
            ptr = (Data*)realloc(vector->pointer, new_size);
            vector->real_size = new_size / sizeof(Data);
        } else {
            ptr = vector->pointer;
        }
    } else {
        ptr = (Data*)malloc(sizeof(Data) * size);
        vector->real_size = size;
    }
        
    if (!ptr) throw std::bad_alloc();
    vector->pointer = ptr;
    vector->size = size;
}

