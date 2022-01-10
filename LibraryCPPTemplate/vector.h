#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <iostream>

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector(): length(0), capacity(0), data(nullptr)
    {
    }

    // Deletes vector structure and internal data
    ~Vector()
    {
        delete[] data;
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const
    {
        return data[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        data[index] = value;
    }

    // Retrieves current vector size
    size_t size() const
    {
        return length;
    }

    void data_copy(Data* new_data, size_t size, size_t offset_old_data = 0, size_t offset_new_data = 0) {
        for (int i = 0; i < size; ++i) {
            new_data[offset_new_data + i] = data[offset_old_data + i];
        }
    }

    void expand_data(size_t size) {
        if (capacity >= size)
            return;
        if (capacity == 0)
            capacity = 1;
        while (capacity < size)
            capacity *= capacity_multiply;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t size)
    {
        if (capacity < size) {
            expand_data(size);
            Data* new_data = new Data[capacity];
            data_copy(new_data, this->size());
            delete[] data;
            data = new_data;
        }
        length = size;
    }

protected:
    size_t length;
    size_t capacity;
    const int capacity_multiply = 2;
    Data* data;
};

#endif