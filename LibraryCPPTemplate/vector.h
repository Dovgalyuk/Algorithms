#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector() : data_(nullptr), size_(0), capacity_(0)
    {
    }

    // copy constructor
    Vector(const Vector &a) : data_(nullptr), size_(a.size_), capacity_(a.capacity_)
    {
        if (size_ > 0) {
            data_ = new Data[size_];
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = a.data_[i];
            }
        }
    }

    // assignment operator
    Vector &operator=(const Vector &a)
    {
        if (this == &a)
            return *this;

        Vector temp(a);
        std::swap(data_, temp.data_);
        std::swap(size_, temp.size_);
        std::swap(capacity_, temp.capacity_);
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
        if (index >= size_)
            throw std::out_of_range("Vector::get: index out of range");
        return data_[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        if (index >= size_)
            throw std::out_of_range("Vector::set: index out of range");
        data_[index] = value;
    }

    // Retrieves current vector size
    size_t size() const
    {
        return size_;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t size)
    {
        if (size > capacity_) {
            size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            if (new_capacity < size) new_capacity = size;

            Data* new_data = new Data[new_capacity];
            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = data_[i];
            }

            delete[] data_;
            data_ = new_data;
            capacity_ = new_capacity;
        }
        size_ = size;
    }

private:
    // private data should be here
    Data* data_;
    size_t size_;
    size_t capacity_;
};

#endif
