#include "vector.h"
#include <cstdlib>

// Structure to represent the vector
struct Vector {
    Data* data;      // Dynamic array to store the elements
    size_t capacity; // Total capacity of the array
    size_t size;     // Current number of elements
};

// Creates a new vector
Vector* vector_create() {
    Vector* vector = new Vector;
    vector->data = nullptr;
    vector->capacity = 0;
    vector->size = 0;
    return vector;
}

// Deletes a vector, freeing the memory
void vector_delete(Vector* vector) {
    delete[] vector->data;
    delete vector;
}

// Retrieves the element at the specified index
Data vector_get(const Vector* vector, size_t index) {
    if (index < vector->size) {
        return vector->data[index];
    }
    return 0;
}

// Sets the element at the specified index
void vector_set(Vector* vector, size_t index, Data value) {
    if (index < vector->size) {
        vector->data[index] = value;
    }
}

// Retrieves the current size of the vector
size_t vector_size(const Vector* vector) {
    return vector->size;
}

// Changes the vector size (may increase or decrease)
void vector_resize(Vector* vector, size_t size) {
    if (size == vector->size) {
        return; // No need to resize
    }

    if (size > vector->capacity) {
        // If the requested size is greater than the capacity, allocate more memory
        size_t new_capacity = (size > vector->capacity * 2) ? size : vector->capacity * 2;
        Data* new_data = new Data[new_capacity];

        for (size_t i = 0; i < vector->size; ++i) {
            new_data[i] = vector->data[i];
        }

        delete[] vector->data;
        vector->data = new_data;
        vector->capacity = new_capacity;
    }

    vector->size = size;
}