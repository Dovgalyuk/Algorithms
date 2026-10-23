#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector() : data(nullptr), currentSize(0), capacity(0)
    {
    }

    // copy constructor
    Vector(const Vector &a) : data(nullptr), currentSize(a.currentSize), capacity(a.capacity)
    {
        if (capacity > 0) {
            data = new Data[capacity];

            for (size_t i = 0; i < currentSize; i++) {
                data[i] = a.data[i];
            }
        }
    }

    // assignment operator
    Vector &operator=(const Vector &a)
    {
        if (this == &a) return *this;

        Vector copy(a);

        Data *oldData = data;
        size_t oldSize = currentSize;
        size_t oldCapacity = capacity;

        data = copy.data;
        currentSize = copy.currentSize;
        capacity = copy.capacity;

        copy.data = oldData;
        copy.currentSize = oldSize;
        copy.capacity = oldCapacity;

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
        if (index < currentSize) return data[index];
        return Data();
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        if (index < currentSize) data[index] = value;
    }

    // Retrieves current vector size
    size_t size() const
    {
        return currentSize;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t size)
    {
        if (size > capacity) {
            size_t newCapacity = capacity;

            if (newCapacity == 0) newCapacity = 1;

            while (newCapacity < size) {
                newCapacity *= 2;
            }

            Data *newData = new Data[newCapacity];

            for (size_t i = 0; i < currentSize; i++) {
                newData[i] = data[i];
            }

            delete[] data;
            data = newData;
            capacity = newCapacity;
        }

        if (size > currentSize) {
            for (size_t i = currentSize; i < size; i++) {
                data[i] = Data();
            }
        }
        currentSize = size;
    }

private:
    // private data should be here
    Data *data;
    size_t currentSize;
    size_t capacity;
};

#endif