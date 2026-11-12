#include "vector.h"
#include <limits>
#include <stdexcept>
#include <utility>

Vector::Vector() : data_(nullptr), size_(0), capacity_(0) {}

Vector::Vector(const Vector &a) : Vector()
{
    resize(a.size_);
    for (size_t i = 0; i < size_; i++) data_[i] = a.data_[i];
}

Vector &Vector::operator=(const Vector &a)
{
    if (this != &a)
    {
        Vector copy(a);
        std::swap(data_, copy.data_);
        std::swap(size_, copy.size_);
        std::swap(capacity_, copy.capacity_);
    }
    return *this;
}

Vector::~Vector() { delete[] data_; }

Data Vector::get(size_t index) const
{
    if (index >= size_) throw std::out_of_range("Vector index out of range");
    return data_[index];
}

void Vector::set(size_t index, Data value)
{
    if (index >= size_) throw std::out_of_range("Vector index out of range");
    data_[index] = value;
}

size_t Vector::size() const { return size_; }

void Vector::resize(size_t size)
{
    if (size > capacity_)
    {
        size_t limit = std::numeric_limits<size_t>::max() / sizeof(Data);
        if (size > limit) throw std::length_error("Vector is too large");
        size_t capacity = capacity_;
        if (capacity == 0) capacity = 1;
        while (capacity < size)
        {
            if (capacity > limit / 2) { capacity = size; break; }
            capacity *= 2;
        }
        Data *data = new Data[capacity];
        for (size_t i = 0; i < size_; i++) data[i] = data_[i];
        delete[] data_;
        data_ = data;
        capacity_ = capacity;
    }
    for (size_t i = size_; i < size; i++) data_[i] = 0;
    size_ = size;
}
