#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

template <typename Data>
class Vector {
public:
    // Creates vector
    Vector() {
       data = nullptr;
       length = 0;
       capacity = 0;
    }

    // Deletes vector structure and internal data
    ~Vector() {
        delete[] data;
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const {
        return data[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value) {
        data[index] = value;
    }

    // Retrieves current vector size
    size_t size() const {
        return length;
    }

    // Reserve memory
    void reserve(size_t size) {
        if (capacity == size) return;
        if (capacity > size && size > length) return;

        if (capacity < size) {
            if (capacity == 0) capacity = 1;

            while (capacity < size)
                capacity *= capacityMultiplier;

        } else if (length > size) {
            capacity = size;
        }

        Data *copy = new Data[capacity];
        size_t copySize = size > length ? length : size;

        if (length != 0)
            for (int i = 0; i < copySize; i++) {
                copy[i] = data[i];
            }

        delete[] data;
        data = copy;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t size) {
        reserve(size);
        length = size;
    }

protected:
    size_t length; // Count of elements
    size_t capacity; // Count of reserved elements

    Data *data;

    static const int capacityMultiplier = 2;
};

#endif
