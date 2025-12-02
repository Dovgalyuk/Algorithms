#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>
#include <algorithm>

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    // copy constructor
    Vector(const Vector& a) : data_(nullptr), size_(0), capacity_(0) {
        resize(a.size_);
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = a.data_[i];
        }
    }

    // assignment operator
    Vector& operator=(const Vector& a) {
        if (this != &a) {
            resize(a.size_);
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = a.data_[i];
            }
        }
        return *this;
    }

    // Deletes vector structure and internal data
    ~Vector()
    {
        delete[] data_;
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const
    {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        if (index >= size_) throw std::out_of_range("Index out of range");
        data_[index] = value;
    }

    // Retrieves current vector size
    size_t size() const
    {
        return size_;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t new_size) {
        size_t old_size = size_;
        if (new_size > capacity_) {
            size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
            while (new_capacity < new_size) new_capacity *= 2;
            Data* new_data = new Data[new_capacity];
            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = data_[i];
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = new_capacity;
        }
        size_ = new_size;
        if (new_size > old_size) {
            for (size_t i = old_size; i < new_size; ++i) {
                data_[i] = Data();
            }
        }
    }

    // Access operator for nested vectors
    Data& operator[](size_t index) {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }

    // Const access operator for nested vectors
    const Data& operator[](size_t index) const {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }

private:
    Data* data_;
    size_t size_;
    size_t capacity_;
};

#endif
