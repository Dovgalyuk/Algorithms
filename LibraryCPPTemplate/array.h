#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H
#include <stdlib.h>

typedef int Data;

template <typename Data> class Array
{
public:
    // create array
    Array(unsigned long long);

    // delete array, free memory
    ~Array();

    // returns specified array element
    Data get(unsigned long long index) const;

    // sets the specified array element to the value
    void set(unsigned long long index, Data value);

    // returns array size
    unsigned long long size() const;
	
private:
    Data* _elem;
    unsigned long long _size;
};

template<typename Data>
Array<Data>::Array(unsigned long long val)
{
    _elem = new Data[val];
    _size = val;
    for (int i = 0; i < val; i++)
        _elem[i] = Data();
}

template<typename Data>
Array<Data>::~Array()
{
    delete[] _elem;
}

template<typename Data>
Data Array<Data>::get(unsigned long long index) const
{
    return _elem[index];
}

template<typename Data>
void Array<Data>::set(unsigned long long index, Data value)
{
    _elem[index] = value;
}

template<typename Data>
unsigned long long Array<Data>::size() const
{
    return _size;
}

#endif

