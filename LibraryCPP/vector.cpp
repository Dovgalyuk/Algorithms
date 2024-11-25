#include "vector.h"
#include <cstdlib>

//structure of vector(array with changing size)
struct Vector
{
    Data* data; //dynamic array
    size_t size; //current number of elements
    size_t capacity;//total number of elements, which array can contain 
};

//creating a new vector 
Vector* vector_create()
{
    Vector* vector = new Vector;
    vector->data = nullptr;
    vector->capacity = 0;
    vector->size = 0;
    return vector;
}

//deleting vector fully and also freeing up memory 
void vector_delete(Vector* vector)
{
    delete [] vector->data;
    delete vector;
}

//receiving an element from vector with specific index 
Data vector_get(const Vector* vector, size_t index)
{
    if(index < vector->size){
        return vector->data[index];
    }
    return 0;
}

//placing an element at a specific index 
void vector_set(Vector* vector, size_t index, Data value)
{
    vector->data[index] = value;
}

//receiving the size of the vector 
size_t vector_size(const Vector* vector)
{
    return vector->size;
}

//changing size of the vector 
void vector_resize(Vector* vector, size_t size)
{
    if(size == vector->size){
        return;
    }

    if(size>vector->capacity){
        size_t new_capacity = (size > vector->capacity*2) ? size : vector->capacity*2;
        Data* new_data = new Data[new_capacity];

        for (size_t i = 0;i<vector->size; ++i){
            new_data[i] = vector->data[i];
        }

        delete[] vector->data;
        vector->data = new_data;
        vector->capacity = new_capacity;
    }

    vector->size = size;
}
