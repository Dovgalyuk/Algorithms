#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename Data> class Vector
{
public:
    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    Vector(const Vector &a) : data_(nullptr), size_(0), capacity_(0)
    {
        if (a.size_ > 0)
        {
            data_ = new Data[a.size_];
            for (size_t i = 0; i < a.size_; ++i)
                data_[i] = a.data_[i];
            size_ = capacity_ = a.size_;
        }
    }

    Vector &operator=(const Vector &a)
    {
        if (this != &a)
        {
            if (a.size_ > capacity_)
            {
                Data *new_data = new Data[a.size_];
                for (size_t i = 0; i < a.size_; ++i)
                    new_data[i] = a.data_[i];
                delete[] data_;
                data_ = new_data;
                capacity_ = a.size_;
            }
            else
            {
                for (size_t i = 0; i < a.size_; ++i)
                    data_[i] = a.data_[i];
            }
            size_ = a.size_;
        }
        return *this;
    }

    ~Vector() { delete[] data_; }

    Data get(size_t index) const
    {
        if (index >= size_) throw std::out_of_range("Vector::get: index out of range");
        return data_[index];
    }

    void set(size_t index, Data value)
    {
        if (index >= size_) throw std::out_of_range("Vector::set: index out of range");
        data_[index] = std::move(value);
    }

    size_t size() const { return size_; }

    void resize(size_t size)
    {
        if (size > capacity_)
        {
            size_t newCapacity = (capacity_ == 0) ? 1 : capacity_;
            while (newCapacity < size) newCapacity *= 2;

            Data *newData = new Data[newCapacity];
            for (size_t i = 0; i < size_; ++i)
                newData[i] = std::move(data_[i]);
            delete[] data_;
            data_ = newData;
            capacity_ = newCapacity;
        }

        for (size_t i = size_; i < size; ++i)
            data_[i] = Data();

        size_ = size;
    }

private:
    Data  *data_;
    size_t size_;
    size_t capacity_;
};

#endif