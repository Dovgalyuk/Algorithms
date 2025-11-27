#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

template <typename T>
class Vector
{
public:
    Vector(): data_(nullptr), size_(0), capacity_(0) {}

    Vector(const Vector& a): data_(nullptr), size_(0), capacity_(0)
    {
        copy_from(a);
    }
    
    Vector& operator=(const Vector& a)
    {
        if (this != &a)
        {
            delete[] data_;
            copy_from(a);
        }
        return *this;
    }

    T& operator[](size_t index)
    {
        return data_[index];
    }

    const T& operator[](size_t index) const
    {
        return data_[index];
    }

    ~Vector()
    {
        delete[] data_;
    }

    T get(std::size_t index) const
    {
        if (index >= size_)
        {
            return T();
        }
        return data_[index];
    }

    void set(std::size_t index, T value)
    {
        if (index >= size_)
        {
            return;
        }
        data_[index] = value;
    }
    std::size_t size() const
    {
        return size_;
    }

    void resize(std::size_t new_size)
    {
        if (new_size <= capacity_)
        {
            if (new_size > size_)
            {
                for (std::size_t i = size_; i < new_size; ++i)
                {
                    data_[i] = T();
                }
            }
            size_ = new_size;
            return;
        }

        std::size_t new_capacity = (capacity_ == 0 ? 1 : capacity_);
        while (new_capacity < new_size)
        {
            new_capacity *= 2;
        }

        T* new_data = new T[new_capacity];

        for (std::size_t i = 0; i < size_; ++i)
        {
            new_data[i] = data_[i];
        }
        for (std::size_t i = size_; i < new_size; ++i)
        {
            new_data[i] = T();
        }

        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
        size_ = new_size;
    }

private:
    T* data_;
    std::size_t size_;
    std::size_t capacity_;

    void copy_from(const Vector& a)
    {
        if (a.size_ > 0)
        {
            capacity_ = a.capacity_;
            data_ = new T[capacity_];
            size_ = a.size_;
            for (std::size_t i = 0; i < size_; ++i)
            {
                data_[i] = a.data_[i];
            }
        }
        else
        {
            data_ = nullptr;
            size_ = 0;
            capacity_ = 0;
        }
    }
};

#endif