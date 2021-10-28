#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

template <typename Data> class Array
{
public:
    // create array
    Array(size_t size) : _size(size), arr(new Data[size])
    {

    }

    // delete array, free memory
    ~Array()
    {
        delete []arr;
    }

    // returns specified array element
    Data get(size_t index) const
    {
        return arr[index];
    }

    // sets the specified array element to the value
    void set(size_t index, Data value)
    {
        arr[index] = value;
    }

    // returns array size
    size_t size() const
    {
        return _size;
    }

private:
    // private data should be here
    Data* arr;
    size_t _size;
};


#endif
