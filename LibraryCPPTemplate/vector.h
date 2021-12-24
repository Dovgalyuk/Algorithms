#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector()
    {
        length = 0;
        capacity = 0;
        vector = nullptr;
    }

    // Deletes vector structure and internal data
    ~Vector()
    {
        delete[] vector;
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const
    {
        return vector[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        vector[index] = value;
    }

    // Retrieves current vector size
    int size() const
    {
        return length;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(int newsize)
    {
        if (capacity < newsize)
        {
            expand_vector(newsize);
        }
        length = newsize;
    }

private:
    // private data should be here

    void expand_vector(int newsize)
    {
        if (capacity >= newsize)
            return;
        if (capacity == 0)
            capacity = 1;
        while (capacity < newsize) {
            capacity *= capacityMultiply;
        }
        Data *newVector = new Data[capacity];
        for (size_t i = 0; i < this->length; i++)
        {
            newVector[i] = vector[i];
        }
        delete[] vector;
        vector = newVector;
    }

    int length, capacity;
    const int capacityMultiply = 2;
    Data *vector;
};
#endif
