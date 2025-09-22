#include "array.h"
#include <stdexcept>

Array::Array(size_t size) : size_(size)
{
    data_ = new Data[size];
    for (size_t i = 0; i < size_; i++)
        data_[i] = 0;
}

Array::Array(const Array &a) : size_(a.size_)
{
    data_ = new Data[a.size_];
    for (size_t i = 0; i < size_; i++)
        data_[i] = a.data_[i];
}

Array& Array::operator=(const Array &a)
{
    if (this != &a)
    {
        delete[] data_;
        size_ = a.size_;
        data_ = new Data[size_];
        for (size_t i = 0; i < size_; i++)
            data_[i] = a.data_[i];
    }
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
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

void Array::set(size_t index, Data value)
{
    if (index >= size_) 
    {
        throw std::out_of_range("Index out of range");
    }
    data_[index] = value;
}

size_t Array::size() const
{
    return size_;
}