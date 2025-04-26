#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>
#include <algorithm>

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector()
       : data(new Data[1]), vectorSize(0), volume(1) {}

    // copy constructor
    Vector(const Vector& other)
        : data(new Data[other.volume]), vectorSize(other.vectorSize), volume(other.volume) {
        for (size_t i = 0; i < vectorSize; ++i) {
            data[i] = other.data[i];
        }
    }

    // assignment operator
    Vector& operator=(const Vector& a) {
        if (this != &a) {
            Data* newData = new Data[a.volume];
            for (size_t i = 0; i < a.vectorSize; ++i) {
                newData[i] = a.data[i];
            }
            delete[] data;
            data = newData;
            vectorSize = a.vectorSize;
            volume = a.volume;
        }
        return *this;
    }

    // Deletes vector structure and internal data
    ~Vector() {
        delete[] data;
    }

    // Access to the element (can change)
    Data& operator[](size_t index) {
        if (index >= vectorSize) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Access to the element (read-only)
    const Data& operator[](size_t index) const {
        if (index >= vectorSize) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Iterators
    Data* begin() { return data; }
    Data* end() { return data + vectorSize; }

    const Data* begin() const { return data; }
    const Data* end() const { return data + vectorSize; }

    // Delete an item by index
    void erase(size_t index) {
        if (index >= vectorSize) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = index; i < vectorSize - 1; ++i) {
            data[i] = data[i + 1];
        }
        --vectorSize;
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const {
        if (index >= vectorSize) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value) {
        if (index >= vectorSize) {
            throw std::out_of_range("Index out of range");
        }
        data[index] = value;
    }

    // Retrieves current vector size
    size_t size() const {
        return vectorSize;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t newSize) {
        if (newSize <= volume) {
            vectorSize = newSize;
            return;
        }

        size_t newVolume = std::max(newSize, volume * 2);
        Data* newData = new Data[newVolume];

        for (size_t i = 0; i < vectorSize; ++i) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        volume = newVolume;
        vectorSize = newSize;
    }

    void push(Data value) {
        if (vectorSize >= volume) {
            resize(vectorSize + 1);
        }
        data[vectorSize++] = value;
    }

private:
    Data* data;
    size_t vectorSize;
    size_t volume;
};

#endif
