#include "array.h"
#include "iostream"
#include "stdexcept"

Array::Array(size_t size) : _data(new Data[size]), _size(size)
{
}

Array::Array(const Array &a) : _data(new Data[a._size]), _size(a._size)
{
    for (size_t i = 0; i < a._size; i++){
          _data[i] = a._data[i];
    }
}

Array &Array::operator=(const Array &a)
{
    if (this == &a){ 
        return *this;
    }
    delete[] _data;
    _size = a._size;
    _data = new Data[a._size];
    
    for (size_t i = 0; i < a._size; i++){
        _data[i] = a._data[i];
    }
    return *this;
}

Array::~Array()
{
    delete[] _data;
}

Data Array::get(size_t index) const
{
    if(index >= _size || index < 0) {
        throw std::out_of_range("Индекс вне диапазона");
    }    
    return _data[index];
}

void Array::set(size_t index, Data value)
{
    if(index >= _size || index < 0) {
        throw std::out_of_range("Индекс вне диапазона");
    } 
    _data[index] = value;
}

size_t Array::size() const
{
    return _size;
}
