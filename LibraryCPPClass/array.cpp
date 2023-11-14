#include "array.h"

Array::Array(size_t size)
{
    // this->arr = new Data[size];
    // this->_size = size;
}

Array::Array(const Array &a)
{
    // this->_size = a._size;
    // this->arr = new Data[a._size];
    // for (size_t i = 0; i < a._size; i++)
    //     this->arr[i] = a.arr[i];
}

Array &Array::operator=(const Array &a)
{
    // delete[] this->arr;
    // this->_size = a._size;
    // this->arr = new Data[a._size];
    // for (size_t i = 0; i < a._size; i++)
    // {
    //     this->arr[i] = a.arr[i];
    // }
    return *this;
}

Array::~Array()
{
    // delete[] this->arr;
    // this->arr = nullptr;
}

Data Array::get(size_t index) const
{
    return 0; // this->arr[index];
}

void Array::set(size_t index, Data value)
{
    // this->arr[index] = value;
}

size_t Array::size() const
{
    return 0; // this->_size;
}
