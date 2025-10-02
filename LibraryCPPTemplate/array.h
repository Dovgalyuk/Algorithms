#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename Data> class Array
{
public:
    // create array
    explicit Array(size_t size) : m_size(size)
        , m_data(size ? new Data[size]() : nullptr)
    {
    }

    // copy constructor
    Array(const Array &a) : m_size(a.m_size)
        , m_data(m_size ? new Data[m_size] : nullptr)
    {
        if (m_data)
        {
            std::copy(a.m_data, a.m_data + m_size, m_data);
        }
    }

    // assignment operator
    Array &operator=(const Array &a)
    {
        if (this != &a)
        {
            Array temp(a);
            swap(temp);
        }
        return *this;
    }

    // delete array, free memory
    ~Array()
    {
        delete[] m_data;
    }

    // returns specified array element
    Data get(size_t index) const
    {
        if (index >= m_size)
        {
            throw std::out_of_range("Index out of range");
        }
        return m_data[index];
    }

    // sets the specified array element to the value
    void set(size_t index, Data value)
    {
        if (index >= m_size)
        {
            throw std::out_of_range("Index out of range");
        }
        m_data[index] = value;
    }

    // returns array size
    size_t size() const
    {
        return m_size;
    }

private:
    // private data should be here
    void swap(Array& other) noexcept
    {
        std::swap(m_size, other.m_size);
        std::swap(m_data, other.m_data);
    }

    size_t m_size{ 0 };
    Data* m_data{ nullptr };
};

#endif
