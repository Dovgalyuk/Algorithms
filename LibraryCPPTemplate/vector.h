#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>

template <typename Data> class Vector
{
private:
    const size_t INCREASE_SIZE = 2;
    Data* arr;
    size_t size_v;
    size_t capacity;

public:
    // Creates vector
    Vector() :  arr(nullptr), size_v(0), capacity(0)
    {
    }

    // copy constructor
    Vector(const Vector &a) : arr(nullptr), size_v(a.size_v), capacity(a.capacity)
    {
        arr = new Data[capacity];
        for (size_t i = 0; i < size_v; ++i) {
            arr[i] = a.arr[i];
        }
    }

    // assignment operator
    Vector& operator=(const Vector& other)
    {
        if (this != &other)
        {
            Data* new_arr = nullptr;
            if (other.arr != nullptr) {
                new_arr = new Data[other.capacity];
                for (size_t i = 0; i < other.size_v; i++)
                {
                    new_arr[i] = other.arr[i];
                }
            }
            delete[] arr;
            arr = new_arr;
            size_v = other.size_v;
            capacity = other.capacity;
        }
        return *this;
    }

    // Deletes vector structure and internal data
    ~Vector()
    {
        delete[] arr;
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const
    {
        if(index >= size_v) {
            throw std::out_of_range("Vector index out of range");
        }
        return arr[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        if(index >= size_v) {
            throw std::out_of_range("Vector index out of range");
        }
        arr[index] = value;
    }

    // Retrieves current vector size
    size_t size() const
    {
        return size_v;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t size)
    {
        if (size > capacity) {
            if (capacity == 0) {
                capacity = 1;
            }
            while (size > capacity) {
                capacity *= INCREASE_SIZE;
            }

            Data* old_arr = arr;
            arr = new Data[capacity];

            if (old_arr != nullptr) {
                for(size_t i = 0; i < size_v; i++) {
                    arr[i] = old_arr[i];
                }
                delete[] old_arr;
            }
        }
        size_v = size;
    }
};

#endif
