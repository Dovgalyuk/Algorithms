#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>

template<typename Data>
class Vector
{
public:
    Vector() : arr(new Data[4]), s(0), cap(4)
    {}

    Vector(size_t size) : arr(new Data[size]), s(size), cap(size)
    {
        for (size_t i = 0; i < s; i++)
            arr[i] = Data();
    }

    Vector(size_t size, const Data& default_value) : arr(new Data[size]), s(size), cap(size)
    {
        for (size_t i = 0; i < s; i++)
            arr[i] = default_value;
    }

    Vector(const Vector& other) : arr(new Data[other.cap]), s(other.s), cap(other.cap)
    {
        for (size_t i = 0; i < s; i++)
            arr[i] = other.arr[i];
    }

    Vector(Vector&& other) : arr(other.arr), s(other.s), cap(other.cap)
    {
        other.arr = nullptr;
        other.s = 0;
        other.cap = 0;
    }

    Vector& operator=(const Vector& other)
    {
        if (this != &other)
        {
            delete[] arr;
            cap = other.cap;
            s = other.s;
            arr = new Data[cap];

            for (size_t i = 0; i < s; i++)
                arr[i] = other.arr[i];
        }
        return *this;
    }

    Vector& operator=(Vector&& other)
    {
        if (this != &other)
        {
            delete[] arr;

            arr = other.arr;
            s = other.s;
            cap = other.cap;

            other.arr = nullptr;
            other.s = 0;
            other.cap = 0;
        }
        return *this;
    }

    ~Vector()
    {
        delete[] arr;
    }

    Data& operator[](size_t index)
    {
        return arr[index];
    }

    const Data& operator[](size_t index) const
    {
        return arr[index];
    }

    Data& get(size_t index)
    {
        if (index >= s) throw std::out_of_range("index out of range");
        return arr[index];
    }

    void set(size_t index, const Data& value)
    {
        if (index >= s) throw std::out_of_range("index out of range");
        arr[index] = value;
    }

    size_t size() const
    {
        return s;
    }

    void resize(size_t new_size)
    {
        if (new_size > cap)
            grow(new_size);

        for (size_t i = s; i < new_size; i++)
            arr[i] = Data();

        s = new_size;
    }

    void push_back(const Data& value)
    {
        if (s == cap)
            grow(cap * 2);

        arr[s++] = value;
    }

    void erase(size_t index)
    {
        if (index >= s) throw std::out_of_range("index out of range");

        for (size_t i = index + 1; i < s; i++)
            arr[i - 1] = arr[i];

        s--;
    }

private:
    Data* arr;
    size_t s;
    size_t cap;

    void grow(size_t new_cap)
    {
        if (new_cap < cap * 2)       
            new_cap = cap * 2;
        
        Data* new_arr = new Data[new_cap];

        for (size_t i = 0; i < s; i++)
            new_arr[i] = arr[i];

        delete[] arr;
        arr = new_arr;
        cap = new_cap;
    }
};

#endif
