#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>

template <typename Data> class Vector
{
public:
    Vector() : data_(nullptr), size_(0), capacity_(0)
    {
    }

    Vector(const Vector &other) : data_(nullptr), size_(0), capacity_(0)
    {
        resize(other.size_);
        for (size_t i = 0; i < size_; ++i)
            data_[i] = other.data_[i];
    }

    Vector &operator=(const Vector &other)
    {
        if (this != &other)
        {
            resize(other.size_);
            for (size_t i = 0; i < size_; ++i)
                data_[i] = other.data_[i];
        }
        return *this;
    }

    ~Vector()
    {
        delete[] data_;
    }

    Data get(size_t index) const
    {
        if (index >= size_)
            throw std::out_of_range("Vector index out of range");
        return data_[index];
    }

    void set(size_t index, Data value)
    {
        if (index >= size_)
            throw std::out_of_range("Vector index out of range");
        data_[index] = value;
    }

    size_t size() const
    {
        return size_;
    }

    void resize(size_t size)
    {
        if (size > capacity_)
        {
            size_t new_capacity = capacity_ == 0 ? 1 : capacity_;
            while (new_capacity < size)
            {
                if (new_capacity > static_cast<size_t>(-1) / 2)
                {
                    new_capacity = size;
                    break;
                }
                new_capacity *= 2;
            }
            Data *new_data = new Data[new_capacity]();
            for (size_t i = 0; i < size_; ++i)
                new_data[i] = data_[i];
            delete[] data_;
            data_ = new_data;
            capacity_ = new_capacity;
        }
        for (size_t i = size_; i < size; ++i)
            data_[i] = Data();
        size_ = size;
    }

private:
    Data *data_;
    size_t size_;
    size_t capacity_;
};

#endif
