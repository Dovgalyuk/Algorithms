#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector() : data(nullptr), size_(0), capacity(0)
    {
    }

    // copy constructor
    Vector(const Vector &a) : data(nullptr), size_(0), capacity(0)
    {
        if (a.size_ > 0) {
            data = new Data[a.size_];
            capacity = a.size_;
            size_ = a.size_;
            for (size_t i = 0; i < size_; i++) {
                data[i] = a.data[i];
            }
        }
    }

    // assignment operator
    Vector &operator=(const Vector &a)
    {
        if (this != &a) {
            Data *newData = nullptr;
            if (a.size_ > 0) {
                newData = new Data[a.size_];
                for (size_t i = 0; i < a.size_; i++) {
                    newData[i] = a.data[i];
                }
            }
            delete [] data;
            data = newData;
            size_ = a.size_;
            capacity = a.size_;
        }
        return *this;
    }

    // Deletes vector structure and internal data
    ~Vector()
    {
        delete[] data;
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const
    {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        data[index] = value;
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
        if (size > capacity) {
            size_t newCapacity = capacity == 0 ? 1 : capacity * 2;

            if (newCapacity < size) {
                newCapacity = size;
            }

            Data *newData = new Data[newCapacity];

            for (size_t i = 0; i < size_; i++) {
                newData[i] = data[i];
            }

            delete[] data;
            data = newData;
            capacity = newCapacity;
        }

        if (size > size_) {
            for (size_t i = size_; i < size; i++) {
                data[i] = Data();
            }
        }

        size_ = size;
    }

private:
    // private data should be here
    Data *data;
    size_t size_;
    size_t capacity;
};

#endif
