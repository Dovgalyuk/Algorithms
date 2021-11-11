#ifndef VECTOR_H
#define VECTOR_H
#include <cstddef>

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector(): length(0), capacity(0), vector(nullptr)
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
        if(index <= length)
            vector[index] = value;
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
    void resize(size_t newSize)
    {
        if(capacity < newSize) {
            increaseCapacity(newSize);
            Data* newVector = new Data[capacity];
            copyArray(newVector, this->size());
            delete []vector;
            vector = newVector;
        }
        length = newSize;
    }


private:
    // private data should be here


    void copyArray(Data* newVector, size_t size){
        for (int i = 0; i < size; ++i)
            newVector[i] = vector[i];
    }

    void increaseCapacity(size_t size) {
        if (capacity >= size)
            return;
        if (capacity == 0)
            capacity = 1;
        while (capacity < size)
            capacity *= capacity_increase;
    }

    size_t length;
    size_t capacity;
    const int capacity_increase = 2;
    Data* vector;
};

#endif

