#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

#include <cstddef>
#include <memory>
#include <stdexcept>

template <typename Data> class Array
{
public:
    // create array
    explicit Array(std::size_t size)
        : size_(size), data_(new Data[size]())
    {
    }

    // copy constructor
    Array(const Array &a)
        : size_(a.size_), data_(new Data[a.size_]())
    {
        for (std::size_t i = 0; i < size_; ++i)
            data_[i] = a.data_[i];
    }

    // assignment operator
    Array &operator=(const Array &a)
    {
        if (this == &a)
            return *this;

        if (size_ != a.size_)
            throw std::length_error("Cannot assign arrays with different sizes");

        for (std::size_t i = 0; i < size_; ++i)
            data_[i] = a.data_[i];

        return *this;
    }

    // delete array, free memory
    ~Array() = default;

    // returns specified array element
    Data get(std::size_t index) const
    {
        check_index(index);
        return data_[index];
    }

    // sets the specified array element to the value
    void set(std::size_t index, Data value)
    {
        check_index(index);
        data_[index] = value;
    }

    // returns array size
    std::size_t size() const
    {
        return size_;
    }

private:
    void check_index(std::size_t index) const
    {
        if (index >= size_)
            throw std::out_of_range("Array index is out of range");
    }

    std::size_t size_;
    std::unique_ptr<Data[]> data_;
};

#endif
