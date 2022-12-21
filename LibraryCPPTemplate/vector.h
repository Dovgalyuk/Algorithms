#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector()
    {
        vector_size = 0;
        max_size = 1;
        data = (Data*)max_size;
    }
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
        return vector_size;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t size)
    {
        if (size <= max_size) 
        {
            vector_size = size;
            return;
        }

        size_t _max_size = size * 2;
        Data* new_data = (Data*)_max_size;

        for (size_t i = 0; i < vector_size; i++) 
        {
            new_data[i] = data[i];
        }
        delete[] data;

        data = new_data;
        max_size = _max_size;
        vector_size = size;
    }

private:
    // private data should be here
    Data* data;
    size_t vector_size;
    size_t max_size;
};

#endif
