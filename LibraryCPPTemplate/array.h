#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

template <typename Data> class Array
{
public:
    // create array
    explicit Array(size_t size)
    {
        array_size = size;
        data = new Data[size];
    }

    // copy constructor
    Array(const Array &a)
    {
        array_size = a.array_size;
        data = new Data[array_size];
        for (size_t i = 0; i < array_size; i++ ) {
            data[i] = a.data[i];
        }
    }

    // assignment operator
    Array &operator=(const Array &a)
    {
        if (this == &a) {
            return *this;
        }
        delete[] data;
        array_size = a.array_size;
        data = new Data[array_size];
        for (size_t i = 0; i < array_size; i++) {
            data[i] = a.data[i];
        }
        return *this;
    }

    // delete array, free memory
    ~Array()
    {
        delete[] data;
    }

    // returns specified array element
    Data get(size_t index) const
    {
        return data[index];
    }

    // sets the specified array element to the value
    void set(size_t index, Data value)
    {
        data[index] = value;
    }

    // returns array size
    size_t size() const
    {
        return array_size;
    }

private:
    size_t array_size;
    Data* data; 
};

#endif
