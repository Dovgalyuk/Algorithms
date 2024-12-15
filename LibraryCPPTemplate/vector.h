#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>

template <typename T> class Vector
{
public:
    // Creates vector
    Vector();

    Vector(size_t initial_size);

    // copy constructor
    Vector(const Vector &other);

    // assignment operator
    Vector &operator=(const Vector &other);

    // Deletes vector structure and internal data
    ~Vector();

    // Retrieves vector element with the specified index
    T& get(size_t index) const;

    // Sets vector element with the specified index
    void set(size_t index, T value);

    // Retrieves current vector size
    size_t size() const;
    
    void resize(size_t new_size);

private:
    // private data should be here
    T* elements;
    size_t capacity;
    size_t current_size;  
};

//Constructors

template<typename T>
Vector<T>::Vector():elements(nullptr), capacity(0), current_size(0) {}

template<typename T>
Vector<T>::Vector(size_t initial_capacity):elements(new T[initial_capacity]), capacity(initial_capacity), current_size(0) {}

template<typename T>
Vector<T>::Vector(const Vector& other)
        :elements(new T[other.capacity])
        , capacity(other.capacity)
        , current_size(other.current_size)
{
    for(size_t i = 0; i < other.current_size; i++) {
        elements[i] = other.elements[i];
    }
}

// assignment operator
template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this == &other) {
        return *this;
    }

    delete[] elements;

    capacity = other.capacity;
    current_size = other.current_size;
    elements = new T[capacity];
    for (size_t i = 0; i < current_size; i++) {
        elements[i] = other.elements[i];
    }

    return *this;
}


// Destructor
template<typename T>
Vector<T>::~Vector() {
    delete[] elements; 
}

template<typename T>
T& Vector<T>::get(size_t index) const {
    if (index >= size()) {
        throw std::out_of_range("Index out of range");
    }
    return elements[index];
}

template<typename T>
void Vector<T>::set(size_t index, T value) {
    if (index >= size()) {
        throw std::out_of_range("Index out of range set");
    }
    elements[index] = value;
}

template<typename T>
size_t Vector<T>::size() const{
    return current_size;
}

// Change capacity
template<typename T>
void Vector<T>::resize(size_t new_size) {
    if (new_size > capacity) {
        size_t new_capacity = new_size * 2;
        T* new_elements = new T[new_capacity];
        for (size_t i = 0; i < current_size; ++i) {
            new_elements[i] = elements[i];
        }

        delete[] elements;
        elements = new_elements;
        capacity = new_capacity;
    }
    current_size = new_size;
}


#endif
