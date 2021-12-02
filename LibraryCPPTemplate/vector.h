#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector()
    {
        vector = new Data[_size];
    }

    // Deletes vector structure and internal data
    ~Vector()
    {
        delete[]vector;
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const
    {
        return vector[index];
        //return Data();
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        if(index <= _size)
            vector[index]=value;
    }

    // Retrieves current vector size
    size_t size() const
    {
        return _size;
    }


    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t size)
    {
        if (_capacity < size) {
            increaseData(size);
            Data* new_vector = new Data[_capacity];
            for(size_t i = 0 ; i < _size; i++)
                new_vector[i] = vector[i];
            delete[] vector;
            vector = new_vector;
        }
        _size = size;
    }

private:
    // private data should be here
    void increaseData(size_t size) {
        if (_capacity == 0)
            _capacity = 1;
        while (_capacity < size)
            _capacity *= 2;
    }

    size_t _size;
    Data *vector;
    size_t _capacity;
};

#endif
