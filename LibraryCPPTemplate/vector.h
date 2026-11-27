#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector()
    {
    }

    // copy constructor
    Vector(const Vector &a)
    {
        size_ = a.size_;
        capacity_ = a.size_;
        data_ = (capacity_ > 0) ? new Data[capacity_] : nullptr;
        for (size_t i = 0; i < size_; ++i)
        {
            data_[i] = a.data_[i];
        }
    }

    // assignment operator
    Vector &operator=(const Vector &a)
    {
        if (this != &a)
        {
            delete[] data_;
            size_ = a.size_;
            capacity_ = a.size_;
            data_ = (capacity_ > 0) ? new Data[capacity_] : nullptr;
            for (size_t i = 0; i < size_; ++i)
            {
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
        return data_[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
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
            size_t new_capacity = (capacity_ == 0) ? 1 : capacity_;
            while (new_capacity < size)
            {
                new_capacity *= 2;
            }
            Data *new_data = new Data[new_capacity];
            for (size_t i = 0; i < size_; ++i)
            {
                new_data[i] = data_[i];
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = new_capacity;
        }
        for (size_t i = size_; i < size; ++i)
        {
            data_[i] = Data();
        }
        size_ = size;
    }

private:
    Data *data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
};

#endif
