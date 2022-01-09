#include "vector.h"

struct Vector
{
    Data* data_;
    size_t size_;
    size_t capacity_;

    Vector() : size_(0), capacity_(10){
        data_ = new Data [capacity_];
    }
    ~Vector(){
        delete[] data_;
        size_ = 0;
        capacity_ = 0;
    }
};

Vector *vector_create()
{
    return new Vector;
}

void vector_delete(Vector *vector)
{
    delete[] vector;
}

Data vector_get(const Vector *vector, size_t index)
{
    return vector->data_[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    vector->data_[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size_;
}

void vector_resize(Vector *vector, size_t size)
{
    if (vector->capacity_ < size) {
        while(vector->capacity_ < size){
            vector->capacity_ *= 2;
        }
        Data* copied = new Data[vector->capacity_];
        for(size_t i = 0; i < vector->size_; ++i){
            copied[i] = vector->data_[i];
        }
        delete[] vector->data_;
        vector->data_ = copied;

    }
    vector->size_ = size;
}
