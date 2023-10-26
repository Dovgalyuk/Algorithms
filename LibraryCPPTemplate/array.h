#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

template <typename Data>
class Array {
public:
    // create array
    explicit Array(size_t size) {
        this->data = new Data[size];
        this->size_array = size;
    }

    // delete array, free memory
    ~Array() {
        delete[] data;
    }

    // copy constructor
    template <typename T>
    Array(const Array<T>& a) {
        size_array = a.size_array;
        data = new Data[size_array];
        for (size_t i = 0; i < size_array; i++) {
            data[i] = *a.get(i);
        }
    }

    // assignment operator
    template <typename T>
    Array& operator=(const Array<T>& a) {
        if (this == &a) {
            // self-assignment, do nothing
            return *this;
        }

        // delete current data
        delete[] data;

        // deep copy
        size_array = a.size_array;
        data = new Data[size_array];
        for (size_t i = 0; i < size_array; i++) {
            data[i] = *a.get(i);
        }

        return *this;
    }

    // returns specified array element
    Data* get(size_t index) const {
        return &data[index];
    }

    // sets the specified array element to the value
    void set(size_t index, Data value) {
        data[index] = value;
    }
    // returns array size
    size_t size() const { return this->size_array; }

    size_t size_array;
private:
    Data* data;
};

#endif