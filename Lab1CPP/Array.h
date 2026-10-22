#ifndef ARRAY_H
#define ARRAY_H
#include <stdexcept>
using namespace std;
template <typename T>
class Array {
private:
    T *arr ;
    const size_t size;
public:
    Array(size_t size) : size(size) {
        arr = new T[size];
    }

    ~Array() {
        delete[] arr;
    }
    T& operator[](size_t index ) {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        return arr[index];
    }
    const T& operator[](size_t index ) const {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        return  arr[index];
    }
    size_t getSize() const {
        return size;
    }
    Array(const Array& other) : size(other.size){
        arr = new T[other.size];
        for (size_t i = 0 ; i < other.size; i++) {
            arr[i] = other.arr[i];
        }
    }
    Array& operator=(const Array& other) {
        if (this == &other) {
            return *this;
        }

        size_t copySize;

        if (other.size < size) {
            copySize = other.size;
        } else {
            copySize = size;
        }

        for (size_t i = 0; i < copySize; i++) {
            arr[i] = other.arr[i];
        }

        return *this;
    }
};
#endif