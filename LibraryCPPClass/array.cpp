#include "array.h"
#include <stdexcept>

Array::Array(size_t size)
{
    size_ = size;
    data_ = new Data[size_];

    for (size_t i = 0; i < size_; ++i)
    {
        data_[i] = 0;
    }
}

Array::Array(const Array &a)
{
    size_ = a.size_;
    data_ = new Data[size_];

    for (size_t i = 0; i < size_; ++i)
    {
        data_[i] = a.data_[i];
    }
}

Array &Array::operator=(const Array &a)
{
    if (this == &a)
    {
        return *this;
    }
    
    Data *copy = new Data[a.size_];
    for (size_t i = 0; i < a.size_; ++i)
    {
        copy[i] = a.data_[i];
    }

    delete[] data_;
    data_ = copy;
    size_ = a.size_;
    return *this;
}

Array::~Array()
{
    delete[] data_;
}

Data Array::get(size_t index) const
{
    if (index >= size_)
    {
        throw std::out_of_range("index out of range");
    }
    return data_[index];
}

void Array::set(size_t index, Data value)
{
    if (index >= size_)
    {
        throw std::out_of_range("index out of range");
    }
    data_[index] = value;
}

size_t Array::size() const
{
    return size_;
}
