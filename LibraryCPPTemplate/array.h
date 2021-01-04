#ifndef ARRAY_H
#define ARRAY_H

template <typename Data> class Array
{
public:
    // create array
    Array<Data>(unsigned size)
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
    Data get(unsigned index) const
    {
        return _elem[index];
    }

    // sets the specified array element to the value
    void set(unsigned index, Data value)
    {
        _elem[index] = value;
    }

    // returns array size
    unsigned size() const
    {
        return _size;
    }

private:
    Data* _elem;
    unsigned _size;
};

#endif
