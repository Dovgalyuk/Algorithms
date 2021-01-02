#ifndef ARRAY_H
#define ARRAY_H

using std::size_t;

template <typename Data> class Array
{
public:
    // create array
    Array<Data>(size_t size)
    {
        _elem = new Data[size];
        _size = size;
        for (int i = 0; i < size; i++)
            _elem[i] = 0;
    }

    // delete array, free memory
    ~Array<Data>()
    {
        delete[] _elem;
    }

    // returns specified array element
    Data get(size_t index) const
    {
        return _elem[index];
    }

    // sets the specified array element to the value
    void set(size_t index, Data value)
    {
        _elem[index] = value;
    }

    // returns array size
    size_t size() const
    {
        return _size;
    }

private:
    Data* _elem;
    size_t _size;
};

#endif
