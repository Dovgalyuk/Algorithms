#include "vector.h"
#include <algorithm>

Vector::Vector() : data_(new Data[1]), size_(0), max_size_(1) {}

Vector::Vector(const Vector& a) : data_(new Data[a.max_size_]), size_(a.size_), max_size_(a.max_size_) {
   std::copy(a.data_, a.data_ + a.size_, data_);
}

Vector& Vector::operator=(const Vector& a) {
   if (this != &a) {
       delete[] data_;
       data_ = new Data[a.max_size_];
       size_ = a.size_;
       max_size_ = a.max_size_;
       std::copy(a.data_, a.data_ + a.size_, data_);
   }
   return *this;
}

Vector::~Vector() { delete[] data_; }

Data Vector::get(size_t index) const {
    if (size_ <= index) throw "Error";
    return data_[index];
}

void Vector::set(size_t index, Data value) {
    if (size_ <= index) throw "Error";
    data_[index] = value;
}

size_t Vector::size() const { return size_; }

void Vector::resize(size_t size) {
    if (size <= max_size_) {
        size_ = size;
        return;
    }
    size_t max_max_size = size * 2;
    Data* tmp = new Data[max_max_size];
    for (size_t i = 0; i < size_; i++) {
        tmp[i] = data_[i];
    }
    delete[] data_;
    data_ = tmp;
    max_size_ = max_max_size;
    size_ = size;
}
