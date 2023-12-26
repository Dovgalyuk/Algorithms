#include "array.h"

Array::Array(size_t size)
{
    this->arr = new int[size];
    this->sizet = size;
}

Array::Array(const Array &a)
{
    this->arr = new int[a.sizet];
    for (int i = 0; i < a.sizet; i++)
    {
        this->arr[i] = a.arr[i];
    }
}

Array &Array::operator=(const Array &a)
{
    return *this;
}

Array::~Array()
{
    delete[] arr;
    arr = nullptr; 
}

Data Array::get(size_t index) const
{
    return Data(this->arr[index]);
}

void Array::set(size_t index, Data value)
{
    this->arr[index] = value;
}

size_t Array::size() const
{
    return size_t(this->sizet);
}
