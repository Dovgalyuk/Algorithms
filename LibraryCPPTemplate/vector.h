#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>

template <typename Data> class Vector
{
public:
    Vector() : data(nullptr), sz(0), capacity(0)
    {
    }

    Vector(const Vector& a) : data(copy_data(a)), sz(a.sz), capacity(a.sz)
    {
    }

    Vector& operator=(const Vector& a)
    {
        if (this != &a) {
            Data* new_data = copy_data(a);
            delete[] data;
            data = new_data;
            sz = a.sz;
            capacity = a.sz;
        }
        return *this;
    }

    ~Vector()
    {
        delete[] data;
    }

    Data get(std::size_t index) const
    {
        if (index >= sz)
            throw std::out_of_range("Vector::get: index out of range");
        return data[index];
    }

    void set(std::size_t index, Data value)
    {
        if (index >= sz)
            throw std::out_of_range("Vector::set: index out of range");
        data[index] = value;
    }

    std::size_t size() const
    {
        return sz;
    }

    void resize(std::size_t new_size)
    {
        if (new_size > capacity)
            grow(new_size);

        if (new_size < sz) {
            for (std::size_t i = new_size; i < sz; ++i)
                data[i] = Data();
        }
        else {
            for (std::size_t i = sz; i < new_size; ++i)
                data[i] = Data();
        }
        sz = new_size;
    }

    void push_back(const Data& value)
    {
        if (sz == capacity)
            grow(sz + 1);
        data[sz++] = value;
    }

private:
    void grow(std::size_t needed)
    {
        std::size_t new_cap = (capacity > 0) ? capacity : 1;
        while (new_cap < needed)
            new_cap *= 2;

        Data* new_data = new Data[new_cap]();
        for (std::size_t i = 0; i < sz; ++i)
            new_data[i] = data[i];

        delete[] data;
        data = new_data;
        capacity = new_cap;
    }

    static Data* copy_data(const Vector& a)
    {
        if (a.sz == 0)
            return nullptr;
        Data* new_data = new Data[a.sz]();
        for (std::size_t i = 0; i < a.sz; ++i)
            new_data[i] = a.data[i];
        return new_data;
    }

    Data* data;
    std::size_t sz;
    std::size_t capacity;
};

#endif
