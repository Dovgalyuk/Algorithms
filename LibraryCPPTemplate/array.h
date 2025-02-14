#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

template <typename Data>
class Array
{
public:
    // create array
    explicit Array(size_t size)
    {
        if (size <= 0)
        {
            throw std::invalid_argument("Array size must be greater than 0");
        }
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
        if (index < dataSize)
        {
            data[index] = value;
        }
        else
        {
            throw std::out_of_range("index out of range");
        }
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
