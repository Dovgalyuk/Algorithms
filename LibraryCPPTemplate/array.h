<<<<<<< HEAD
#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

template <typename Data> class Array
{
public:
    // create array
    explicit Array(size_t size)
    {
    }

    // copy constructor
    template <typename T>
    Array(const Array<T> &a)
    {
    }

    // assignment operator
    template <typename T>
    Array &operator=(const Array<T> &a)
    {
        return *this;
    }

    // delete array, free memory
    ~Array()
    {
    }

    // returns specified array element
    Data get(size_t index) const
    {
        return Data(0);
    }

    // sets the specified array element to the value
    void set(size_t index, Data value)
    {
    }

    // returns array size
    size_t size() const
    {
        return 0;
    }

private:
    // private data should be here
};

#endif
=======
#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

template <typename Data> class Array
{
public:
    // create array
    explicit Array(size_t size)
    {
    }

    // copy constructor
    Array(const Array &a)
    {
    }

    // assignment operator
    Array &operator=(const Array &a)
    {
        return *this;
    }

    // delete array, free memory
    ~Array()
    {
    }

    // returns specified array element
    Data get(size_t index) const
    {
        return Data(0);
    }

    // sets the specified array element to the value
    void set(size_t index, Data value)
    {
    }

    // returns array size
    size_t size() const
    {
        return 0;
    }

private:
    // private data should be here
};

#endif
>>>>>>> b58458d4ca9eff800382dfb1b01e13b902ec3548
