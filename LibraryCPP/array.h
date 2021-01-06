//
// Created by Alex on 25.12.2020.
//

#ifndef YURILAB_ARRAY_H
#define YURILAB_ARRAY_H


#include <cstdio>

template <typename Data> class Array
{
public:
    // create array
    explicit Array(size_t size)
    {
        _elem = new Data[size];
        _size = size;
        for (int i = 0; i < size; i++)
            _elem[i] = Data();
    }

    // delete array, free memory
    ~Array()
    {
        delete[] _elem;
    }

    // returns specified array element
    Data get(size_t index) const
    {
        return _elem[index];
    }

    // sets the specified array element to the value
    void set(size_t index, Data value)
    {
        _elem[index] = value;
    }

    // returns array size
    size_t size() const
    {
        return _size;
    }

    Data& operator[](size_t index)
    {
        return _elem[index];
    }
    Data operator[](size_t index) const
    {
        return _elem[index];
    }
private:
    Data* _elem;
    size_t _size;
};


#endif //YURILAB_ARRAY_H
