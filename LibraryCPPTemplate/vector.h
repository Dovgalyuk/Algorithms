#ifndef VECTOR_H
#define VECTOR_H
#include <cstddef>
#include "iostream"

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector(): lenght(0), vec(new Data[lenght])
    {
    }

    // Deletes vector structure and internal data
    ~Vector()
    {
        delete []vec;
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const
    {
        return vec[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        vec[index] = value;
    }

    // Retrieves current vector size
    size_t size() const
    {
        return lenght;
    }

    void copyArray(Data* newVec, size_t size){
        for (int i = 0; i < size; ++i) {
            newVec[i] = vec[i];
        }
    }


    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t newSize)
    {
        if(lenght > newSize) {
            Data *newVec = new Data[newSize];
            copyArray(newVec, newSize);
            delete []vec;
            vec = newVec;
        }
        lenght = newSize;
    }


private:
    // private data should be here
    size_t lenght;
    Data* vec;
};

#endif

