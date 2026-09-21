#include <stdexcept>

class Array {
    private:
    int* data;
    int size;
    public:
    Array (int size) {
        if(size > 0) {
            this->size = size;
            data = new int[size]();
        } else {
            throw std::invalid_argument("Invalid size");
        }
    }
    Array(const Array& other) {
        this->size = other.size;
        data = new int[size];
        for(int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    Array& operator=(const Array& other) {
        if (this == &other) {
            return *this;
        }

        delete[] data;

        size = other.size;
        data = new int[size];

        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }

        return *this;
    }
    ~Array() {
        delete[] data;
    }
    
    int& operator[](int index) {
        if(0 <= index && index < size) {
            return data[index];
        } else {
            throw std::out_of_range("Index out of range");
        }
    }
    const int& operator[](int index) const{
        if(0 <= index && index < size) {
            return data[index];
        } else {
            throw std::out_of_range("Index out of range");
        }
    }
    int getSize() const{
        return size;
    }
    
};