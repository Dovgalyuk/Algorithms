#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <cassert>

template <typename Data> class Vector
{
public:
    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    Vector(const Vector &a) { copyFrom(a); }

    Vector &operator=(const Vector &a)
    {
        if (this != &a)
        {
            delete[] data_;
            copyFrom(a);
        }
        return *this;
    }

    ~Vector() { delete[] data_; }

    Data get(size_t index) const
    {
        assert(index < size_);
        return data_[index];
    }

    void set(size_t index, Data value)
    {
        assert(index < size_);
        data_[index] = value;
    }

    size_t size() const { return size_; }

    void resize(size_t newSize)
    {
        if (newSize <= capacity_)
        {
            for (size_t i = size_; i < newSize; ++i)
                data_[i] = Data();
            size_ = newSize;
            return;
        }

        size_t newCapacity = capacity_ == 0 ? 1 : capacity_;
        while (newCapacity < newSize) newCapacity *= 2;

        Data *newData = new Data[newCapacity];
        for (size_t i = 0; i < size_; ++i)
            newData[i] = data_[i];
        for (size_t i = size_; i < newSize; ++i)
            newData[i] = Data();

        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
        size_ = newSize;
    }

private:
    void copyFrom(const Vector &a)
    {
        size_ = a.size_;
        capacity_ = a.capacity_;
        if (capacity_ == 0)
            data_ = nullptr;
        else
        {
            data_ = new Data[capacity_];
            for (size_t i = 0; i < size_; ++i)
                data_[i] = a.data_[i];
        }
    }

    Data *data_;
    size_t size_;
    size_t capacity_;
};

#endif
