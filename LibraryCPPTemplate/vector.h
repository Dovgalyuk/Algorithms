#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector()
    {
        mSize = 0;
        mCapacity = 0;
        mData = nullptr;
    }

    // copy constructor
    Vector(const Vector &a)
    {
        copyCon(a);
    }

    // assignment operator
    Vector &operator=(const Vector &a)
    {
        if (this != &a) {
            delete[] mData;
            copyCon(a);
        }
        return *this;
    }

    // Deletes vector structure and internal data
    ~Vector()
    {
        delete[] mData;
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const
    {
        return mData[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        mData[index] = value;
    }

    // Retrieves current vector size
    size_t size() const
    {
        return mSize;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t newSize)
    {
        if (newSize == mSize) return;

        if (newSize < mSize) {
            mSize = newSize;
            return;
        }

        if (newSize > mSize) {
            if (newSize <= mCapacity) mSize = newSize;
            else {
                size_t newCapacity = (mCapacity == 0) ? 1 : mCapacity * 2;
                if (newCapacity < newSize) 
                    newCapacity = newSize;

                Data* newData = new Data[newCapacity];

                for (size_t i = 0; i < mSize; i++) 
                    newData[i] = mData[i];

                delete[] mData;

                mData = newData;
                mSize = newSize;
                mCapacity = newCapacity;
            }
        }
    }

private:
    Data* mData;
    size_t mSize;
    size_t mCapacity;

    void copyCon(const Vector& a) {
        mSize = a.mSize;
        mCapacity = a.mCapacity;

        if (a.mData) {
            mData = new Data[mCapacity];
            for (size_t i = 0; i < mSize; i++) 
                mData[i] = a.mData[i];
        } else 
            mData = nullptr;
    }
};

#endif
