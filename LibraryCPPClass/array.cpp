#include "array.h"
#include <stdexcept>


Array::Array(size_t size) : size_(size), data_(new Data[size])
{
    if (data_ == nullptr)
    {
        throw std::bad_alloc();
    }
}

Array::Array(const Array &a) :size_(a.size_), data_(new Data[size_])
{
    for (size_t i = 0; i < size_; i++)
    {
        data_[i] = a.data_[i];
    }
}

Array &Array::operator=(const Array &a)
{
    if (&a != this)
    {
        delete[] data_;
        size_ = a.size_;
        data_ = new Data[size_];

        for (size_t i = 0; i < size_; i++)
        {
            data_[i] = a.data_[i];
        }
    }
    return *this;
}

Array::~Array()
{
    delete[] data_;
}

Data Array::get(size_t index) const
{
    if (index >= size_) {
        throw std::out_of_range("Invalid array size");
    }
    else
    {
        return data_[index];
    }
}

void Array::set(size_t index, Data value) {
    if(index >= size_) 
    {
        throw std::out_of_range("Invalid array size");
    }
    else
    {
        data_[index] = value;
    }
}

size_t Array::size() const
{
    return size_;
}
