#include "array.h"

template<typename Data>
inline Array<Data>::Array(size_t size)
{
    _elem = new Data[size];
    _size = size;
    for (int i = 0; i < size; i++)
        _elem[i] = 0;
}

template<typename Data>
Array<Data>::~Array()
{
    delete[] _elem;
}

template<typename Data>
Data Array<Data>::get(size_t index) const
{
    return _elem[index];
}

template<typename Data>
void Array<Data>::set(size_t index, Data value)
{
    _elem[index] = value;
}

template<typename Data>
size_t Array<Data>::size() const
{
    return _size;
}
