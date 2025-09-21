#include "array.h"

Array::Array(size_t size) : size_(size), data_(new Data[size])
{
    if (data_ == nullptr)
    {
        throw std::bad_alloc();
    }
    for (int i = 0; i < size_; i++)
    {
        data_[i] = Data(0);
    }
}

Array::Array(const Array &other) :size_(other.size_)
{
    data_ = new Data[size_];
    for (int i = 0; i < size_; i++)
    {
        data_[i] = other.data_[i];
    }
}

Array &Array::operator=(const Array &other)
{
    if (this != &other)
    {
        delete[] data_;
        size_ = other.size_;
        data_ = new Data[size_];

        for (int i = 0; i < size_; i++)
        {
            data_[i] = other.data_[i];
        }
    }
    return *this;
}
Data& Array::operator[](size_t index)
{
    if (index >= size_)
    {
        throw std::out_of_range("ERROR: index out of range");
    }
    else
    {
        return data_[index];
    }
}
Array::~Array()
{
    delete[] data_;
}

Data Array::get(size_t index) const
{
    if ((index >= size_))
    {
        throw std::out_of_range("ERROR: index out of range");
    }
    else
    {
        return data_[index];
    }

}

void Array::set(size_t index, Data value) {

    if ((index >= size_))
    {
        throw std::out_of_range("Your index out of range");
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
