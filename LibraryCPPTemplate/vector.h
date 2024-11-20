#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>


template <typename Data> class Vector
{
public:
    // Creates vector
    Vector();

    Vector(size_t size);

    // copy constructor
    Vector(const Vector &a);

    // assignment operator
    Vector &operator=(const Vector &a);

    // Deletes vector structure and internal data
    ~Vector();

    // Retrieves vector element with the specified index
    Data& get(size_t index) const;

    // Sets vector element with the specified index
    void set(size_t index, Data value);

    // Retrieves current vector size
    size_t size() const;
    
    void resize(size_t new_size);

private:
    // private data should be here
    Data* data;
    size_t m_capacity;
    size_t m_size;  
};

//Constructors

template<typename Data>
Vector<Data>::Vector():data(nullptr), m_capacity(0), m_size(0) {}

template<typename Data>
Vector<Data>::Vector(size_t initCap):data(new Data[initCap]), m_capacity(initCap), m_size(0) {}

template<typename Data>
Vector<Data>::Vector(const Vector& other)
        :data(new Data[other.m_capacity])
        , m_capacity(other.m_capacity)
        , m_size(other.m_size)
{
    for(size_t i = 0; i < other.m_size; i++) {
        data[i] = other.data[i];
    }
}

// assignment operator
template<typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& other) {
    if (this == &other) {
        return *this;
    }

    delete[] data;

    m_capacity = other.m_capacity;
    m_size = other.m_size;
    data = new Data[m_capacity];
    for (size_t i = 0; i < m_size; i++) {
        data[i] = other.data[i];
    }

    return *this;
}


// Destructor
template<typename Data>
Vector<Data>::~Vector() {
    delete[] data; 
}

template<typename Data>
Data& Vector<Data>::get(size_t index) const {
    if (index >= size()) {
        std::out_of_range("Index out of range");
    }
    return data[index];
}

template<typename Data>
void Vector<Data>::set(size_t index, Data value) {
    if (index >= size()) {
        std::out_of_range("Index out of range set");
    }
    data[index] = value;
}

template<typename Data>
size_t Vector<Data>::size() const{
    return m_size;
}

// Change m_capacity
template<typename Data>
void Vector<Data>::resize(size_t new_size) {
    if (new_size > m_capacity) {
        size_t new_capacity = new_size * 2;
        Data* newData = new Data[new_capacity];
        for (size_t i = 0; i < m_size; ++i) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        m_capacity = new_capacity;
    }
    m_size = new_size;
}



#endif