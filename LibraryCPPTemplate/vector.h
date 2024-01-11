#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <algorithm>

template <typename Data>
class Vector
{
public:
    Vector() : data_(new Data[1]), size_(0), max_size_(1) {}

    Vector(const Vector& a) : data_(new Data[a.max_size_]), size_(a.size_), max_size_(a.max_size_) {
        std::copy(a.data_, a.data_ + a.size_, data_);
    }
    Vector &operator=(const Vector &a)
    {
        if (this != &a) {
            Data* new_data = new Data[a.max_size_];
            std::copy(a.data_, a.data_ + a.size_, new_data);
            delete[] data_;
            data_ = new_data;
            size_ = a.size_;
            max_size_ = a.max_size_;
        }
        return *this;
    }
    ~Vector() {
        delete[] data_;
    }

    Data get(size_t index) const {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }

    void set(size_t index, Data value) {
        if (index >= size_) throw std::out_of_range("Index out of range");
        data_[index] = value;
    }

    size_t size() const { return size_; }

    void resize(size_t size) {
        if (size <= max_size_) {
            size_ = size;
            return;
        }
        size_t new_max_size = size * 2;
        Data* new_data = new Data[new_max_size];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        max_size_ = new_max_size;
        size_ = size;
    }

    void push_back(Data value) {
        while (size_ >= max_size_) {
            size_t new_max_size = max_size_ * 2;
            Data* new_data = new Data[new_max_size];
            for (size_t i = 0; i < size_; i++) {
                new_data[i] = data_[i];
            }
            delete[] data_;
            data_ = new_data;
            max_size_ = new_max_size;
        }
        data_[size_] = value;
        size_++;
    }
private:
    Data* data_;
    size_t size_;
    size_t max_size_;
};

#endif
