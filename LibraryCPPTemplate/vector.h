#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <limits>
#include <memory>
#include <utility>
#include <stdexcept>

template <typename Data> class Vector
{
public:
    const Data &at(size_t index) const
    {
        if (index >= count) {
            throw std::out_of_range("wrong vector index");
        }
        return data[index];
    }
    // Creates vector
    Vector() : data(nullptr), count(0), capacity(0)
    {
    }

    // copy constructor
    Vector(const Vector &a) : data(nullptr), count(0), capacity(0)
    {
    std::unique_ptr<Data[]> new_data(new Data[a.count]());
    for (size_t i = 0; i < a.count; i++)
        new_data[i] = a.data[i];
    data = new_data.release();
    count = a.count;
    capacity = a.count;
    }

    // assignment operator
    Vector &operator=(const Vector &a)
    {
    if (this == &a) return *this;
    Vector temp(a);
    swap(temp);
    return *this;
    }

    // Deletes vector structure and internal data
    ~Vector()
    {
        delete[] data;
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const
    {
        if (index >= count) return Data();
        return data[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        if (index >= count) return;
        data[index] = value;
    }

    // Retrieves current vector size
    size_t size() const
    {
        return count;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t size) // скопировал с предышей лабы, только чуть изменил, ибо cpp не очень
    {
        const size_t maxsize = std::numeric_limits<size_t>::max() / sizeof(Data);
        if (size > maxsize) return;
        if (size == count) return;
        if (size > capacity) {
            size_t newcap = capacity;
            if (!newcap) newcap = 1;
            while (newcap < size) {
                if (newcap > maxsize / 2) {
                    newcap = size;
                    break;
                }
                newcap *= 2;
            }
            std::unique_ptr<Data[]> new_data(new Data[newcap]());
            for (size_t i = 0; i < count; i++) new_data[i] = data[i];
            delete[] data;
            data = new_data.release();
            capacity = newcap;
        } else if (size < count) {
            // capacity оставляем, чтобы потом не выделять память заново
            for (size_t i = size; i < count; i++) data[i] = Data();
        }
        count = size;
    }

    void swap(Vector &other) noexcept
    {
        std::swap(data, other.data);
        std::swap(count, other.count);
        std::swap(capacity, other.capacity);
    }

private:
    Data *data;
    size_t count;
    size_t capacity;
};

#endif
