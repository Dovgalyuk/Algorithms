#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

#include <cstring>

template <typename Data>
class Array
{
public:
    // Create empty array
    Array() : mSize(0), mArray(nullptr) {}

    // create array
    explicit Array(std::size_t size) : mSize(size),
                                       mArray(mSize ? new Data[mSize] : nullptr) {}

    // copy constructor
    Array(const Array &other) : mSize(other.mSize),
                                mArray(mSize ? new Data[mSize] : nullptr)
    {
        other.copyTo(*this);
    }

    // Move constructor
    Array(const Array &&other) noexcept : Array()
    {
        swap(*this, other);
    }

    // assignment operator
    Array &operator=(Array other)
    {
        swap(*this, other);
        return *this;
    }

    // delete array, free memory
    ~Array()
    {
        delete[] mArray;
    }

    // returns specified array element
    Data get(std::size_t index) const
    {
        return mArray[index];
    }

    Data &operator[](std::size_t index) const
    {
        return mArray[index];
    }

    // sets the specified array element to the value
    void set(std::size_t index, Data value)
    {
        mArray[index] = value;
    }

    // returns array size
    std::size_t size() const
    {
        return mSize;
    }

    friend void swap(Array &first, Array &second)
    {
        using std::swap;
        swap(first.mSize, second.mSize);
        swap(first.mArray, second.mArray);
    }

    void copyTo(Array &output) const
    {
        std::memcpy(output.mArray, mArray, sizeof(Data) * std::min(mSize, output.mSize));
    }

private:
    // private data should be here
    std::size_t mSize;
    Data *mArray;
};

#endif