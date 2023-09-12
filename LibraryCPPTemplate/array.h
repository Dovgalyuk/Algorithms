#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

template <typename Data>
class Array
{
public:
    // create array
    explicit Array(size_t size)
    {
        ptr = new Data[size];
        this->size = size;
    }

    // copy constructor
    template <typename T>
    Array(const Array<T> &a)
    {
        delete[] ptr;
        ptr = new Data[a.size];
        for (size_t i = 0; i < a.size; i++)
            ptr[i] = (Data)a.ptr[i];
    }

    // assignment operator
    template <typename T>
    Array &operator=(const Array<T> &a)
    {
        this->~Array();
        this = Array(a);
        return *this;
    }

    // delete array, free memory
    ~Array()
    {
        delete[] ptr;
    }

    // returns specified array element
    Data get(size_t index) const
    {
        return ptr[index];
    }

    // sets the specified array element to the value
    void set(size_t index, Data value)
    {
        prt[index] = value;
    }

    // returns array size
    size_t size() const
    {
        return size;
    }

private:
    // private data should be here
    Data *ptr = nullptr;
    size_t size = 0;
};

#endif
