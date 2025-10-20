#include "vector.h"
#include <algorithm>

Vector::Vector() : data_(nullptr), size_(0), capacity_(0)
{}

void Vector::copy_from(const Vector& a)
{
    if (a.size_ > 0) {
        capacity_ = a.capacity_;
        data_ = new Data[capacity_];
        size_ = a.size_;
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = a.data_[i];
        }
    } else {
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
    }
}

Vector::Vector(const Vector& a) : data_(nullptr), size_(0), capacity_(0)
{
    copy_from(a);
}

Vector& Vector::operator=(const Vector& a)
{
    if (this != &a) {
        delete[] data_;
        
        copy_from(a);
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
        return Data();
    }
    return data_[index];
}

void Vector::set(size_t index, Data value)
{
    if (index >= size_) {
        return;
    }
    data_[index] = value;
}

size_t Vector::size() const
{
    return size_;
}

void Vector::resize(size_t new_size)
{
    if (new_size == size_) {
        return;
    }

    if (new_size <= capacity_) {
        size_ = new_size;
        return;
    }

    size_t new_capacity = capacity_ == 0 ? 1 : capacity_;
    while (new_capacity < new_size) {
        new_capacity *= 2;
    }

    Data* new_data = new Data[new_capacity];

    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }

    for (size_t i = size_; i < new_size; ++i) {
        new_data[i] = Data();
    }

    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
    size_ = new_size;
}
