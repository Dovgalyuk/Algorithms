#include "myvector.h"
#include <algorithm>
#include <stdexcept>

using namespace std;
Vector::Vector() : data_(nullptr), size_(0), vmestimost_(0) {}

Vector::Vector(const Vector &a)
    : data_(new Data[a.vmestimost_]), size_(a.size_), vmestimost_(a.vmestimost_){
        copy(a.data_, a.data_ + a.size_, data_);
    }


Vector &Vector::operator=(const Vector &a)
{
    if (this != &a) {
        delete[] data_;
        vmestimost_ = a.vmestimost_;
        size_ = a.size_;
        data_ = new Data[vmestimost_];
        copy(a.data_, a.data_ + a.size_, data_);
    }
    return *this;
}

Vector::~Vector()
{
    delete[] data_;
}
void Vector::reserve(size_t new_vmestimost) {
    if (new_vmestimost <= vmestimost_) return;
    Data* new_data = new Data[new_vmestimost];
    copy(data_, data_ + size_, new_data);
    delete[] data_;
    data_ = new_data;
    vmestimost_ = new_vmestimost;
}

Data Vector::get(size_t index) const
{
    if (index >= size_) {
        throw out_of_range("index vectora vne diapozona");
    }
    return data_[index];

}

void Vector::set(size_t index, Data value)
{
    if (index >= size_) {
        throw out_of_range("index vectora vne diapozona");
    }
    data_[index] = value;
}

size_t Vector::size() const
{
    return size_;
}

void Vector::resize(size_t new_size)
{
    if (new_size > vmestimost_) {
        reserve(max(new_size, max(vmestimost_ * 2, (size_t)1)));
    }
    size_ = new_size;
}
