#ifndef VECTOR_H
#define VECTOR_H
#include <cstddef>

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector(): length(0), vector(new Data[length])
    {
    }

    // Deletes vector structure and internal data
    ~Vector()
    {
        delete []vector;
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
    size_t size() const
    {
        return length;
    }

    void copyArray(Data* newVector, size_t size){
        for (int i = 0; i < size; ++i) {
            newVector[i] = vector[i];
        }
    }


    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t newSize)
    {
        if(length < newSize) {
            Data* newVector = new Data[newSize];
            copyArray(newVector, length);
            delete []vector;
            vector = newVector;
        }
        length = newSize;
    }


private:
    // private data should be here
    size_t length;
    Data* vector;
};

#endif