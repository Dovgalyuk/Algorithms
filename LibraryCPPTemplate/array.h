#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

template <typename Data> class Array
{
public:
    // create array
    explicit Array(size_t size)
    {
        mSize = size;
        mData = new Data[mSize];
    }

    // copy constructor
    Array(const Array &a)
    {
        mSize = a.mSize;
        mData = new Data[mSize];
        for (size_t i = 0; i < mSize; i++)
            mData[i] = a.mData[i];
    }

    // assignment operator
    Array &operator=(const Array &a)
    {
        if (this != &a) {
            delete[] mData;
            mSize = a.mSize;
            mData = new Data[mSize];
            for (size_t i = 0; i < mSize; i++)
            mData[i] = a.mData[i];
        }
        return *this;
    }

    // delete array, free memory
    ~Array()
    {
        delete[] mData;
    }

    // returns specified array element
    Data get(size_t index) const
    {
        return mData[index];
    }

    // sets the specified array element to the value
    void set(size_t index, Data value)
    {
        mData[index] = value;
    }

    // returns array size
    size_t size() const
    {
        return mSize;
    }

private:
    Data* mData;
    size_t mSize;
};

#endif
