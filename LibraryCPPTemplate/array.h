#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

template <typename T> class Array
{
public:
    // create array
    Array(size_t size);

    // delete array, free memory
    ~Array();

    // returns specified array element
    T get(size_t index) const;

    // sets the specified array element to the value
    void set(size_t index, T value);

    // returns array size
    size_t size() const;

    T& operator[](size_t index);
    T operator[](size_t index) const;
private:
    T* _elem;
    size_t _size;
};

#endif
