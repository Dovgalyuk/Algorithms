#include "vector.h"

#include <utility>

Vector::Vector() : data_(nullptr), size_(0), capacity_(0) {}

Vector::Vector(const Vector& a)
    : data_(a.capacity_ == 0 ? nullptr : new Data[a.capacity_]), size_(a.size_), capacity_(a.capacity_) {
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = a.data_[i];
    }
}

Vector& Vector::operator=(const Vector& a) {
    if (this == &a)
        return *this;

    Vector tmp(a);
    std::swap(size_, tmp.size_);
    std::swap(data_, tmp.data_);
    std::swap(capacity_, tmp.capacity_);

    return *this;
}

Vector::~Vector() { delete[] data_; }

const Data& Vector::get(size_t index) const { return data_[index]; }

void Vector::set(size_t index, const Data& value) { data_[index] = value; }

size_t Vector::size() const { return size_; }

void Vector::resize(size_t new_size) {
    if (new_size > capacity_) {
        size_t double_capacity = capacity_ * 2;
        capacity_ = (new_size > double_capacity) ? new_size : double_capacity;
        Data* new_data = new Data[capacity_];

        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }

        delete[] data_;
        data_ = new_data;
    }
    if (new_size > size_) {
        for (size_t i = size_; i < new_size; ++i)
            data_[i] = Data();
    }

    size_ = new_size;
}
