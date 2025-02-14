#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

template <typename Data>
class Array
{
public:
    // create array
    explicit Array(size_t size)
    {
        dataSize = size;
        data = new Data[size];
    }

    // copy constructor
    Array(const Array& a)
    {
        dataSize = a.dataSize;
        data = a.data;
    }

    // assignment operator
    Array& operator=(const Array& a)
    {
        return *this;
    }

    // delete array, free memory
    ~Array()
    {
        delete[] data;
    }

    // returns specified array element
    Data get(size_t index) const
    {
        return data[index];
    }

    // sets the specified array element to the value
    void set(size_t index, Data value)
    {
        data[index] = value;
    }

    // returns array size
    size_t size() const
    {
        return dataSize;
    }

private:
    size_t dataSize;
    Data* data;
};

#endif
