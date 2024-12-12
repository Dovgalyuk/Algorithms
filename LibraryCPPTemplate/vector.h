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
    Vector(const Vector &vec);

    // assignment operator
    Vector &operator=(const Vector &vec);

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
    size_t capacity;
    size_t sizee;
};

//Constructors
template<typename Data>
Vector<Data>::Vector():data(nullptr), capacity(0), sizee(0) {}

template<typename Data>
Vector<Data>::Vector(size_t initCap):data(new Data[initCap]), capacity(initCap), sizee(0) {}

template<typename Data>
Vector<Data>::Vector(const Vector& vec)
        :data(new Data[vec.capacity])
        , capacity(vec.capacity)
        , sizee(vec.sizee)
{
    for(size_t i = 0; i < vec.sizee; i++) {
        data[i] = vec.data[i];
    }
}

// assignment operator
template<typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vec) {
    if (this == &vec) {
        return *this;
    }

    delete[] data;

    capacity = vec.capacity;
    sizee = vec.sizee;
    data = new Data[capacity];
    for (size_t i = 0; i < sizee; i++) {
        data[i] = vec.data[i];
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
        std::out_of_range("out of range");
    }
    return data[index];
}

template<typename Data>
void Vector<Data>::set(size_t index, Data value) {
    if (index >= size()) {
        std::out_of_range("out of range set");
    }
    data[index] = value;
}

template<typename Data>
size_t Vector<Data>::size() const{
    return sizee;
}

// Change capacity
template<typename Data>
void Vector<Data>::resize(size_t new_size) {
    if (new_size > capacity) {
        size_t new_capacity = new_size * 2;
        Data* newData = new Data[new_capacity];
        for (size_t i = 0; i < sizee; ++i) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        capacity = new_capacity;
    }
    sizee = new_size;
}



#endif