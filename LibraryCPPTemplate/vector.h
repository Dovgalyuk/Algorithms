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
    Vector(const Vector &a) : data_(nullptr), size_(a.size_), capacity_(a.size_)
    {
        if (capacity_ > 0)
        {
            data_ = new Data[capacity_]();
            for (size_t i = 0; i < size_; ++i)
                data_[i] = a.data_[i];
        }
    }

    // assignment operator
    Vector &operator=(const Vector &a)
    {
        if (this != &a)
        {
            Vector tmp(a);
            std::swap(data_, tmp.data_);
            std::swap(size_, tmp.size_);
            std::swap(capacity_, tmp.capacity_);
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
        check(index);
        return data_[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        check(index);
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
        if (size > capacity_)
        {
            size_t new_capacity = capacity_ * 2;
            if (new_capacity < size)
                new_capacity = size;
            reallocate(new_capacity);
        }
        else if (size < size_)
        {
            for (size_t i = size; i < size_; ++i)
                data_[i] = Data();
            if (size * 4 <= capacity_ && capacity_ > MIN_SHRINK_CAPACITY)
                reallocate(capacity_ / 2);
        }
        size_ = size;
    }

private:
    static const size_t MIN_SHRINK_CAPACITY = 8;

    Data *data_;
    size_t size_;
    size_t capacity_;

    void check(size_t index) const
    {
        if (index >= size_)
            throw std::out_of_range("Vector: index out of range");
    }

    void reallocate(size_t new_capacity)
    {
        Data *new_data = new Data[new_capacity]();
        const size_t keep = size_ < new_capacity ? size_ : new_capacity;
        for (size_t i = 0; i < keep; ++i)
            new_data[i] = data_[i];
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }
};

#endif
