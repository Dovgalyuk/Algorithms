#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

template <typename T> class Array
{
public:
    // create array
    Array(size_t size)
    {
        _elem = new T[size];
        _size = size;
    }

    // delete array, free memory
    ~Array()
    {
        delete[] _elem;
    }

    // returns specified array element
    T get(size_t index) const
    {
        return _elem[index];
    }

    // sets the specified array element to the value
    void set(size_t index, T value)
    {
        _elem[index] = value;
    }

    // returns array size
    size_t size() const
    {
        return _size;
    }

    void copy_values(Array<T>* from)
    {
        for (int i = 0; i < from->size(); i++)
        {
            _elem[i] = from->get(i);
        }
    }

private:
    T* _elem;
    size_t _size;
    // private data should be here
};

#endif
