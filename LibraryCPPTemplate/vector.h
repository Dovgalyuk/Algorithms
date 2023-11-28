#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include "array.h"
#include <stdexcept>

const float vector_prebuffer_ratio = 1.9f;

template <typename Data>
class Vector
{
public:
    // Creates vector
    Vector() : mArray(), mEnd(0)
    {
    }

    // copy constructor
    Vector(const Vector &a) : mArray(a.mArray), mEnd(0) {}

    // assignment operator
    Vector &operator=(Vector &a)
    {
        swap(*this, a);
        return *this;
    }

    // Deletes vector structure and internal data
    // ~Vector() {}

    // Retrieves vector element with the specified index
    Data get(std::size_t index) const
    {
        if (index >= mEnd)
            std::runtime_error("out of bounds");

        return mArray[index];
    }

    Data &operator[](std::size_t index) const
    {
        if (index >= mEnd)
            std::runtime_error("out of bounds");

        return mArray[index];
    }

    // Sets vector element with the specified index
    void set(std::size_t index, Data value)
    {
        if (index >= mEnd)
            std::runtime_error("out of bounds");

        mArray[index] = value;
    }

    // Retrieves current vector size
    std::size_t size() const
    {
        return mEnd;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(std::size_t size)
    {
        if (size > mArray.size() || size < mArray.size() / vector_prebuffer_ratio)
        {
            std::size_t newSize = size * vector_prebuffer_ratio;
            Array<Data> newArray(newSize);
            mArray.copyTo(newArray);
            mArray = newArray;
            mEnd = size;
        }
        else
            mEnd = size;
    }

    friend void swap(Vector &first, Vector &second)
    {
        using std::swap;
        swap(first.mArray, second.mArray);
    }

private:
    // private data should be here
    Array<Data> mArray;
    // index of after last element, similar end iterator in the STL.
    std::size_t mEnd = 0;
};

#endif
