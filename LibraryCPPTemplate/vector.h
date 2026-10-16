#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <utility>

using namespace std;

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector(){
        data = nullptr;
        currentSize = 0;
        capacity = 0;
    }

    // copy constructor
    Vector(const Vector& a) {
        currentSize = a.currentSize;
        capacity = currentSize;
        data = nullptr;
        if (capacity > 0) {
            data = new Data[capacity]{};
            for (size_t i = 0; i < currentSize; i++) {
                data[i] = a.data[i];
            }
        }
    }


    // assignment operator
    Vector& operator=(const Vector& a) {
        if (this == &a) {
            return *this;
        }
        Vector copy(a);
        std::swap(data, copy.data);
        std::swap(currentSize, copy.currentSize);
        std::swap(capacity, copy.capacity);
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
        return data[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        data[index] = value;
    }

    // Retrieves current vector size
    size_t size() const
    {
        return currentSize;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t newSize) {
        if (newSize > capacity) {
            size_t newCapacity = capacity;
            if (newCapacity == 0) {
                newCapacity = 1;
            }
            while (newCapacity < newSize) {
                if (newCapacity > static_cast<size_t>(-1) / 2) {
                    newCapacity = newSize;
                    break;
                }

                newCapacity *= 2;
            }
            Data* newData = new Data[newCapacity]{};
            for (size_t i = 0; i < currentSize; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
        for (size_t i = currentSize; i < newSize; i++) {
            data[i] = Data{};
        }
        currentSize = newSize;
    }

private:
    // private data should be here
    Data* data;
    size_t currentSize;
    size_t capacity;
};

#endif
