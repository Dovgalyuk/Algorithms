#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <algorithm>
using namespace std;
template <typename Data> 
class Vector
{
private:
    Data* data_;
    size_t size_;
    size_t capacity_;

public:
    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    Vector(size_t size, const Data& value = Data()) : size_(size), capacity_(size)
    {
        data_ = new Data[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = value;
        }
    }

    Vector(const Vector &a) : size_(a.size_), capacity_(a.capacity_)
    {
        data_ = new Data[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = a.data_[i];
        }
    }

    Vector &operator=(const Vector &a)
    {
        if (this != &a) {
            delete[] data_;
            size_ = a.size_;
            capacity_ = a.capacity_;
            data_ = new Data[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = a.data_[i];
            }
        }
        return *this;
    }

    ~Vector()
    {
        delete[] data_;
    }
    Data get(size_t index) const
    {
        return data_[index];
    }

    void set(size_t index, Data value)
    {
        data_[index] = value;
    }

    size_t size() const
    {
        return size_;
    }

    void resize(size_t size)
    {
        if (size > capacity_) {
            size_t new_capacity = std::max(size, capacity_ * 2);
            Data* new_data = new Data[new_capacity];
            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = data_[i];
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = new_capacity;
        }
        
        if (size > size_) {
            for (size_t i = size_; i < size; ++i) {
                data_[i] = Data();
            }
        }
        
        size_ = size;
    }

    void push_back(const Data& value)
    {
        if (size_ >= capacity_) {
            size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            Data* new_data = new Data[new_capacity];
            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = data_[i];
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = new_capacity;
        }
        data_[size_++] = value;
    }

    void erase(size_t index)
    {
        for (size_t i = index; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }
        --size_;
    }

    Data& operator[](size_t index)
    {
        return data_[index];
    }

    const Data& operator[](size_t index) const
    {
        return data_[index];
    }
};

#endif