#include <stdlib.h>
#include "array.h"

template<typename T>
inline Array<T>::Array(size_t size)
{
    _elem = new T[size];
    _size = size;
    for (int i = 0; i < size; i++)
        _elem[i] = T();
}

template<typename T>
Array<T>::~Array()
{
    delete[] _elem;
}

template<typename T>
T Array<T>::get(size_t index) const
{
    return _elem[index];
}

template<typename T>
void Array<T>::set(size_t index, T value)
{
    _elem[index] = value;
}

template<typename T>
size_t Array<T>::size() const
{
    return _size;
}

template<typename T>
T& Array<T>::operator[](size_t index)
{
    return _elem[index];
}

template<typename T>
T Array<T>::operator[](size_t index) const
{
    return _elem[index];
}
