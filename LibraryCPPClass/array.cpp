#include "array.h"

Array::Array(size_t size) {
    size_ = size;
    data_ = new Data[size_];
}

Array::Array(const Array& a) {
    size_ = a.size_;
    data_ = new Data[size_];
    for (size_t i = 0; i < size_; i++)  data_[i] = a.data_[i];

}

Array& Array::operator=(const Array& a) {
    if (this != &a) {
        Array temp(a);
        Data* temp_data = data_;
        data_ = temp.data_;
        temp.data_ = temp_data;
        size_t temp_size = size_;
        size_ = temp.size_;
        temp.size_ = temp_size;
    }
    return *this;
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
