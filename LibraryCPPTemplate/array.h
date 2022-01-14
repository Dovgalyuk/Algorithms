#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

template <typename Data> class Array {
public:
    // create array
    Array(size_t size) {
        arraySize = size;
        data = new Data[size];
    }

    // delete array, free memory
    ~Array() {
        delete[] data;
    }

    // returns specified array element
    Data get(size_t index) const
    {
        return data[index];
    }

    // sets the specified array element to the value
    void set(size_t index, Data value) {
        data[index] = value;
    }

    // returns array size
    size_t size() const {
        return arraySize;
    }

private:
    Data *data;
    size_t arraySize;
};

#endif