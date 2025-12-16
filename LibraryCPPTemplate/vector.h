#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <utility>

template <typename Data>
class Vector
{
public:
    Vector()
        : data_(nullptr), size_(0), capacity_(0)
    {
    }

    Vector(const Vector &other)
        : data_(nullptr), size_(0), capacity_(0)
    {
        copyFrom(other);
    }

    Vector(Vector &&other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_)
    {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    Vector &operator=(const Vector &other)
    {
        if (this != &other)
        {
            delete[] data_;
            data_ = nullptr;
            size_ = 0;
            capacity_ = 0;
            copyFrom(other);
        }
        return *this;
    }

    Vector &operator=(Vector &&other) noexcept
    {
        if (this != &other)
        {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    ~Vector()
    {
        delete[] data_;
    }

    std::size_t size() const
    {
        return size_;
    }

    void resize(std::size_t newSize)
    {
        if (newSize <= capacity_)
        {
            if (newSize > size_)
            {
                for (std::size_t i = size_; i < newSize; ++i)
                {
                    data_[i] = Data();
                }
            }
            size_ = newSize;
            return;
        }

        std::size_t newCapacity = capacity_ == 0 ? 1 : capacity_;
        while (newCapacity < newSize)
        {
            newCapacity *= 2;
        }

        Data *newData = new Data[newCapacity];
        for (std::size_t i = 0; i < size_; ++i)
        {
            newData[i] = data_[i];
        }
        for (std::size_t i = size_; i < newSize; ++i)
        {
            newData[i] = Data();
        }

        delete[] data_;
        data_ = newData;
        size_ = newSize;
        capacity_ = newCapacity;
    }

    Data &get(std::size_t index)
    {
        return data_[index];
    }

    const Data &get(std::size_t index) const
    {
        return data_[index];
    }

    void set(std::size_t index, const Data &value)
    {
        if (index < size_)
        {
            data_[index] = value;
        }
    }

private:
    Data *data_;
    std::size_t size_;
    std::size_t capacity_;

    void copyFrom(const Vector &other)
    {
        if (other.size_ == 0)
        {
            return;
        }
        data_ = new Data[other.size_];
        for (std::size_t i = 0; i < other.size_; ++i)
        {
            data_[i] = other.data_[i];
        }
        size_ = other.size_;
        capacity_ = other.size_;
    }
};

#endif
