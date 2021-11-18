#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <iostream>

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector()
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

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t newSize)
    {
        if (capacity < newSize) {
            expand_data(newSize);
            Data* new_data = new Data[capacity];
            for (int i = 0; i < length; ++i) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
        }
        length = newSize;
    }

private:
    void expand_data(size_t size) {
        if (capacity >= size)
            return;
        if (capacity == 0)
            capacity = 1;
        while (capacity < size)
            capacity *= capacity_multiply;
    }

protected:
    size_t length = 0;
    size_t capacity = 0;
    Data* data = nullptr;

    const int capacity_multiply = 2;
};

#endif
