#include "vector.h"
#include <stdexcept>
#include <utility>

Vector::Vector() : data_(nullptr), size_(0), capacity_(0)
{
}

Vector::Vector(const Vector &a) : data_(nullptr), size_(a.size_), capacity_(a.size_)
{
    if (size_ > 0) {
        data_ = new Data[size_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = a.data_[i];
        }
    }
}

Vector &Vector::operator=(const Vector &a)
{
    if (this == &a) {
        return *this;
    }

    Vector temp(a);
    std::swap(data_, temp.data_);
    std::swap(size_, temp.size_);
    std::swap(capacity_, temp.capacity_);
    return *this;
}

Vector::~Vector()
{
    delete[] data_;
}

Data Vector::get(size_t index) const
{
    if (index >= size_) {
        throw std::out_of_range("Vector::get: index out of range");
    }
    return data_[index];
}

void Vector::set(size_t index, Data value)
{
    if (index >= size_) {
        throw std::out_of_range("Vector::set: index out of range");
    }
    data_[index] = value;
}

size_t Vector::size() const
{
    return size_;
}

void Vector::resize(size_t size)
{
    if (size > capacity_) {
        ensureCapacity(size);
    }
    size_ = size;
}

void Vector::ensureCapacity(size_t needed) {
    size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
    if (new_capacity < needed) {
        new_capacity = needed;
    }

    Data* new_data = new Data[new_capacity];
    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }

    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}
