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


    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t size) {

        if (size <= capacity) {
            length = size;
        }
        else {
            if (capacity == 0) {
                capacity = 1;
            }

            while (capacity < size) {
                capacity *= 2;
            }

            Data* new_data = new Data[capacity];
            for (size_t i = 0; i < length; i++) {
                new_data[i] = data[i];
            }

            delete[] data;
            data = new_data;
            length = size;
        }

    }

protected:
    size_t length; // Count of elements
    size_t capacity; // Count of reserved elements

    Data* data;
};

#endif