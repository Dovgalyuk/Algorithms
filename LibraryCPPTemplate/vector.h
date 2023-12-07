#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector()
    {
        vectorSize = 0;
        maxSize = 1;
        data = new Data[maxSize];
    }

    // copy constructor
    template <typename T>
    Vector(const Vector<T>& a)
    {
        data = new Data[a.maxSize];
        vectorSize = a.vectorSize;
        maxSize = a.maxSize;
        for (size_t i = 0; i < vectorSize; i++) {
            data[i] = a.data[i];
        }
    }

    // assignment operator
    template <typename T>
    Vector& operator=(const Vector<T>& a)
    {
        if (this != &a) {
            delete[] data;
            vectorSize = a.vectorSize;
            maxSize = a.maxSize;
            data = new Data[maxSize];

            for (size_t i = 0; i < vectorSize; i++) {
                data[i] = a.data[i];
            }
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
        if (index < vectorSize) {
            return data[index];
        }
        else {
            throw std::out_of_range("Index out of range");
        }
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        if (index < vectorSize) {
            data[index] = value;
        }
        else {
            throw std::out_of_range("Index out of range");
        }
    }

    // Retrieves current vector size
    size_t size() const
    {
        return vectorSize;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t size)
    {
        if (size <= maxSize) {
            vectorSize = size;
            return;
        }

        maxSize = size * 2;
        Data* _data = new Data[maxSize];
        for (size_t i = 0; i < vectorSize; i++) {
            _data[i] = data[i];
        }
        delete[] data;
        data = _data;
        vectorSize = size;
    }

private:
    Data* data;
    size_t vectorSize;
    size_t maxSize;
};

#endif
