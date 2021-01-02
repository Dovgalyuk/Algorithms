#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

typedef int Data;

template <typename Data> class Array
{
public:
    // create array
    Array(size_t size);

    // delete array, free memory
    ~Array();

    // returns specified array element
    Data get(size_t index) const;

    // sets the specified array element to the value
    void set(size_t index, Data value);

    // returns array size
    size_t size() const;
	
private:
    Data* _elem;
    size_t _size;
};

template<typename Data>
Array<Data>::Array(size_t size)
{
    _elem = new Data[size];
    _size = size;
    for (int i = 0; i < size; i++)
        _elem[i] = Data();
}

template<typename Data>
Array<Data>::~Array()
{
    delete[] _elem;
}

template<typename Data>
Data Array<Data>::get(size_t index) const
{
    return _elem[index];
}

template<typename Data>
void Array<Data>::set(size_t index, Data value)
{
    _elem[index] = value;
}

template<typename Data>
size_t Array<Data>::size() const
{
    return _size;
}

#endif

