#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>

template <typename Data> class Vector {
public:
    Vector() : data(nullptr), currentSize(0), capacity(0) {}

    Vector(const Vector& a) : data(nullptr), currentSize(a.currentSize), capacity(a.capacity) {
        if (capacity > 0) {
            data = new Data[capacity]();
            for (size_t i = 0; i < currentSize; i++) data[i] = a.data[i];
        }
    }

    Vector& operator=(const Vector& a) {
        if (this != &a) {
            Vector temp(a);
            Data* tempData = data;
            data = temp.data;
            temp.data = tempData;
            size_t tempSize = currentSize;
            currentSize = temp.currentSize;
            temp.currentSize = tempSize;
            size_t tempCap = capacity;
            capacity = temp.capacity;
            temp.capacity = tempCap;
        }
        return *this;
    }

    ~Vector() {
        delete[] data;
    }

    Data get(size_t index) const {
        return data[index];
    }

    void set(size_t index, Data value) {
        data[index] = value;
    }

    size_t size() const {
        return currentSize;
    }

    void resize(size_t newSize) {
        if (newSize <= capacity) {
            for (size_t i = currentSize; i < newSize; i++) data[i] = Data();
            currentSize = newSize;
            return;
        }
        size_t newCapacity = (capacity == 0) ? 1 : capacity;
        while (newCapacity < newSize) newCapacity *= 2;
        Data* newData = new Data[newCapacity]();
        for (size_t i = 0; i < currentSize; i++) newData[i] = data[i];
        delete[] data;
        data = newData;
        currentSize = newSize;
        capacity = newCapacity;
    }

private:
    Data* data;
    size_t currentSize;
    size_t capacity;
};

#endif
