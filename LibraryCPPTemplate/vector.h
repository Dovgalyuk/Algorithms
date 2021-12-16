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
        if (size > 0)
        resize(length+size);
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average

    void resize(size_t size) {

        size_t resized = size + length;
        Data* copy = new Data[resized];

        if (resized > length) {
           for(int i = 0; i < length;i++)
               data[i] = copy[i];
        }
        else {
            for (int i = 0; i < resized; i++)
                data[i] = copy[i];
        }
        delete[] data;
        data = copy;
        
    }
protected:
    size_t length;
    Data* data;
};

#endif