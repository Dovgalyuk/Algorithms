#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

template <typename Data>
class Array
{
public:
    // create array
    explicit Array(size_t length)
    {
        ptr = new Data[length];
        this->_size = length;
    }

    // copy constructor
    template <typename T>
    Array(Array<T> &a)
    {
        ptr = new Data[a._size];
        for (size_t i = 0; i < a._size; i++)
            ptr[i] = (Data)a.ptr[i];
    }

    // assignment operator
    template <typename T>
    Array &operator=(const Array<T> &a)
    {
        delete[] ptr;
        ptr = new Data[a._size];
        for (size_t i = 0; i < a._size; i++)
            ptr[i] = (Data)a.ptr[i];
        _size = a._size;
        return *this;
    }

    // delete array, free memory
    ~Array()
    {
        delete[] ptr;
        ptr = nullptr;
        _size = 0;
    }

    // returns specified array element
    Data get(size_t index) const
    {
        return ptr[index];
    }

    // sets the specified array element to the value
    void set(size_t index, Data value)
    {
        ptr[index] = value;
    }

    // returns array size
    size_t size() const
    {
        return _size;
    }

private:
    // private data should be here
    Data *ptr = nullptr;
    size_t _size;
};

#endif
