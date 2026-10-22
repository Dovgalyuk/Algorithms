#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>

template <typename Data> class Vector
{
public:
    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    Vector(const Vector &other) : data_(nullptr), size_(0), capacity_(0)
    {
        resize(other.size_);
        copy_from(other);
    }

    Vector &operator=(const Vector &other)
    {
        if (this != &other)
        {
            resize(other.size_);
            copy_from(other);
        }
        return *this;
    }

    ~Vector() { delete[] data_; }

    Data &get(std::size_t index)
    {
        check(index);
        return data_[index];
    }

    const Data &get(std::size_t index) const
    {
        check(index);
        return data_[index];
    }

    void set(std::size_t index, Data value)
    {
        check(index);
        data_[index] = value;
    }

    std::size_t size() const { return size_; }

    void resize(std::size_t new_size)
    {
        if (new_size > capacity_) grow(new_size);
        for (std::size_t i = size_; i < new_size; ++i)
            data_[i] = Data();
        size_ = new_size;
    }

    void push_back(const Data &value)
    {
        if (size_ == capacity_) grow(size_ + 1);
        data_[size_++] = value;
    }

    void erase(std::size_t index)
    {
        check(index);
        for (std::size_t i = index; i + 1 < size_; ++i)
            data_[i] = data_[i + 1];
        --size_;
    }

private:
    void check(std::size_t index) const
    {
        if (index >= size_) throw std::out_of_range("Vector index out of range");
    }

    void grow(std::size_t needed)
    {
        std::size_t new_capacity = capacity_ == 0 ? 1 : capacity_;
        while (new_capacity < needed)
        {
            if (new_capacity > static_cast<std::size_t>(-1) / 2)
            {
                new_capacity = needed;
                break;
            }
            new_capacity *= 2;
        }
        Data *new_data = new Data[new_capacity]();
        for (std::size_t i = 0; i < size_; ++i)
            new_data[i] = data_[i];
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    void copy_from(const Vector &other)
    {
        for (std::size_t i = 0; i < size_; ++i)
            data_[i] = other.data_[i];
    }

    Data *data_;
    std::size_t size_;
    std::size_t capacity_;
};

#endif