#include "vector.h"

Vector::Vector() : data_(nullptr), size_(0), capacity_(0) {}

Vector::Vector(const Vector& a) {
    size_ = a.size_;
    capacity_ = a.capacity_;
    data_ = new Data[capacity_];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = a.data_[i];
    }
}

Vector& Vector::operator=(const Vector& a) {
    if (this != &a) {
        Vector temp(a);
        Data* temp_data = data_; data_ = temp.data_; temp.data_ = temp_data;
        size_t temp_size = size_; size_ = temp.size_; temp.size_ = temp_size;
        size_t temp_cap = capacity_; capacity_ = temp.capacity_; temp.capacity_ = temp_cap;
    }
    return *this;
}

Vector::~Vector() {
    delete[] data_;
}

Data Vector::get(size_t index) const {
    return data_[index];
}

void Vector::set(size_t index, Data value) {
    data_[index] = value;
}

size_t Vector::size() const {
    return size_;
}

void Vector::resize(size_t size) {
    if (size <= capacity_) {
        size_ = size;
        return;
    }

    size_t new_capacity = capacity_ == 0 ? 1 : capacity_;
    while (new_capacity < size) {
        new_capacity *= 2;
    }

    Data* new_data = new Data[new_capacity];
    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }

    delete[] data_;
    data_ = new_data;
    size_ = size;
    capacity_ = new_capacity;
}
