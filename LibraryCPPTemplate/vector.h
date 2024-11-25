#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H
#include <stdexcept>
using namespace std;

template<typename Data>
class Vector {
public:
    Vector() {
        vectorSize = 0;
        volume = 1;
        data = new Data[volume];
    }
    
    ~Vector() {
        delete[] data;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data; 
            vectorSize = other.vectorSize;
            volume = other.volume;
            data = new Data[volume];
            for (size_t i = 0; i < vectorSize; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }


    Data& operator[](size_t index) {
        if (index < vectorSize) {
            return data[index];
        }
        else {
            throw std::out_of_range("Index out of range");
        }
    }


    const Data& operator[](size_t index) const {
        if (index < vectorSize) {
            return data[index];
        }
        else {
            throw std::out_of_range("Index out of range");
        }
    }


    Data* begin() {
        return data; 
    }

    Data* end() {
        return data + vectorSize; 
    }

    void erase(size_t index) {
        if (index >= vectorSize) {
            throw std::out_of_range("Index out of range");
        }

       
        for (size_t i = index; i < vectorSize - 1; ++i) {
            data[i] = data[i + 1];
        }
        vectorSize--; 
    }

    
    Data get(size_t index) const {
        if (index < vectorSize)
            return data[index];
        else
            throw std::out_of_range("Index out of range");
    }


    void set(size_t index, Data value) {
        if (index < vectorSize)
            data[index] = value;
        else
            throw std::out_of_range("Index out of range");
    }


    size_t size() const {
        return vectorSize;
    }

    void swap_data(Vector& other) {
        std::swap(data, other.data);
        std::swap(vectorSize, other.vectorSize);
        std::swap(volume, other.volume);
    }

    void resize(size_t size) {
         if (size <= volume)
        {
            vectorSize = size;  
            return;
        }

        size_t volume1 = size * 2;
        Data* new_data = new Data[volume1];

        for (size_t i = 0; i < vectorSize; i++)  
        {
            new_data[i] = data[i];
        }

        delete[] data;  
        data = new_data;  
        volume = volume1;
        vectorSize = size;  
    }


private:
    Data* data;
    size_t vectorSize;
    size_t volume;
};
#endif