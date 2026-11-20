#include "array.h"

#include <stdexcept>
#include <utility>

Array::Array(size_t size) : data_(new Data[size]()), size_(size) {}

Array::Array(const Array& a) : data_(new Data[a.size_]), size_(a.size_) {
    for (size_t i = 0; i < size_; i++) {
        data_[i] = a.data_[i];
    }
}

Array& Array::operator=(const Array& a) {
    if (this == &a) {
        return *this;
    }
    if (size_ != a.size_) {
        throw std::invalid_argument("size mismatch");
    }

    Array tmp(a);
    std::swap(data_, tmp.data_);

    return *this;
}

Array::~Array() { delete[] data_; }

Data Array::get(size_t index) const { return Data(data_[index]); }

void Array::set(size_t index, Data value) { data_[index] = value; }

size_t Array::size() const { return size_; }
