#include "array.h"

Array::Array(size_t size) {
    size_ = size;
    data_ = new Data[size];
}

Array::~Array() {
    delete[] data_;
}

Data Array::get(size_t index) const {
    return data_[index];
}

void Array::set(size_t index, Data value) {
    data_[index] = value;
}

size_t Array::size() const {
    return size_;
}
