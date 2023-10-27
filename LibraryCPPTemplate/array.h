#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

template <typename Data>
class Array
{
public:
    // create array
    explicit Array(size_t length)
    {
        _ptr = new Data[length];
        _size = length;
    }

    // copy constructor
    template <typename T>
    Array(const Array<T> &a)
    {
        _ptr = new Data[a._size];
        for (size_t i = 0; i < a._size; i++)
            _ptr[i] = (Data)a._ptr[i];
    }

    // assignment operator
    template <typename T>
    Array &operator=(const Array<T> &a)
    {
        delete[] _ptr;
        _ptr = new Data[a._size];
        for (size_t i = 0; i < a._size; i++)
            _ptr[i] = (Data)a._ptr[i];
        this->_size = a._size;
        return *this;
    }

    // delete array, free memory
    ~Array()
    {
        delete[] _ptr;
        _ptr = nullptr;
    }

    // returns specified array element
    Data get(size_t index) const
    {
        return _ptr[index];
    }

    // sets the specified array element to the value
    void set(size_t index, Data value)
    {
        _ptr[index] = value;
    }

    // returns array size
    size_t size() const
    {
        return _size;
    }

private:
    // private data should be here
    Data *_ptr = nullptr;
    size_t _size = 0;
};

#endif
