#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

template<typename Data>
class Vector {
public:
    // Creates vector
    Vector() : size_(0), capacity_(10) {
        data_ = new Data[capacity_];
    }

    // Deletes vector structure and internal data
    ~Vector() {
        delete[] data_;
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const {
        return data_[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value) {
        data_[index] = value;
    }

    // Retrieves current vector size
    size_t size() const {
        return size_;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t size) {
        if (capacity_ < size) {
            while(capacity_ < size){
                capacity_ *= 2;
            }
            Data* copied = new Data[capacity_];
            for(size_t i = 0; i < size_; ++i){
                copied[i] = data_[i];
            }
            delete[] data_;
            data_ = copied;

        }
        size_ = size;
    }

private:
    // private data should be here
    Data *data_;
    size_t size_;
    size_t capacity_;

};

#endif
