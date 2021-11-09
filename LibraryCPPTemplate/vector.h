#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <iostream>

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector(): length(0), capacity(0), vec(nullptr)
    {
    }

    // Deletes vector structure and internal data
    ~Vector()
    {
        delete[] vec;
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const
    {
        return vec[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        if(index <= length)
            vec[index] = value;
        else
            return;
    }

    // Retrieves current vector size
    size_t size() const
    {
        return length;
    }


    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t size)
    {
        if (capacity < size) {
            increaseData(size);
            Data* new_data = new Data[capacity];
            copyArray(new_data, this->size());
            delete[] vec;
            vec = new_data;
        }
        length = size;
    }

private:
    // private data should be here
    void copyArray(Data* new_data, size_t size) {
        for (int i = 0; i < size; ++i) {
            new_data[i] = vec[i];
        }
    }

    void increaseData(size_t size) {
        if (capacity >= size)
            return;
        if (capacity == 0)
            capacity = 1;
        while (capacity < size)
            capacity *= capacity_multiply;
    }


    size_t length;
    size_t capacity;
    const int capacity_multiply = 2;
    Data* vec;
};

#endif