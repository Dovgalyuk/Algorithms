#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

typedef int Data;
typedef unsigned long long mysize_t;

template <typename Data> class Array
{
public:
    // create array
    Array(mysize_t val);

    // delete array, free memory
    ~Array();

    // returns specified array element
    Data get(mysize_t index) const;

    // sets the specified array element to the value
    void set(mysize_t index, Data value);

    // returns array size
    mysize_t size() const;
	
private:
    Data* _elem;
    mysize_t _size;
};


template<typename Data>
Array<Data>::Array(mysize_t val)
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
Data Array<Data>::get(mysize_t index) const
{
    return _elem[index];
}

template<typename Data>
void Array<Data>::set(mysize_t index, Data value)
{
    _elem[index] = value;
}

template<typename Data>
mysize_t Array<Data>::size() const
{
    return _size;
}
#endif

