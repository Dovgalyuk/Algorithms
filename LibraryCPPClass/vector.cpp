#include "vector.h"
#include <stdexcept>

Vector::Vector() : data_(nullptr), size_(0), capacity_(0)
{
}

Vector::Vector(const Vector &a) : data_(new Data[a.capacity_]), size_(a.size_), capacity_(a.capacity_)
{
    for (size_t i = 0; i < a.size_; i++) {
        data_[i] = a.data_[i];
    }
}

Vector &Vector::operator=(const Vector &a)
{
    if (this != &a) {
        delete[] data_;
        data_ = new Data[a.capacity_];
        size_ = a.size_;
        capacity_ = a.capacity_;

        for (size_t i = 0; i < size_; i++) {
            data_[i] = a.data_[i];
        }
    }
    return *this;
}

Vector::~Vector()
{
    delete[] data_;
}

Data Vector::get(size_t index) const
{
    if (index >= size_) {
        throw std::out_of_range("Index is out of range");
    }
    return data_[index];
}

void Vector::set(size_t index, Data value)
{
    if (index >= size_) {
        throw std::out_of_range("Index is out of range");
    }
    data_[index] = value;
}

size_t Vector::size() const
{
    return size_;
}

void Vector::resize(size_t new_size)
{
    if (new_size > capacity_) {
        ensure_capacity(std::max(new_size, capacity_ * 2));
    }
    size_ = new_size;
}

void Vector::ensure_capacity(size_t min_capacity) {
    if (min_capacity > capacity_) {
        capacity_ = min_capacity;
        Data *new_data = new Data[capacity_];

        for (size_t i = 0; i < size_; i++) {
            new_data[i] = data_[i];
        }

        delete[] data_;
        data_ = new_data;
    }
}