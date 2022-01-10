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
    size_t size() {
        return arraySize;
    }

    void push_back(Data value) {
        Data* copy_data = new Data[arraySize + 1];
        for (size_t i = 0; i < arraySize; i++) {
            copy_data[i] = data[i];
        }
        copy_data[arraySize] = value;
        delete data;
        data = copy_data;
        arraySize++;
    }

    void delete_index(size_t index) {
        
        Data* copy_data = new Data[arraySize];
        for (size_t i = 0; i < index; i++) {
            copy_data[i] = data[i];
        }

        arraySize--;
        
        for (size_t i = index; i < arraySize; i++) {
            copy_data[i] = data[i+1];
        }

        delete data;
        data = copy_data;
       
    }



private:
    Data* data;
    size_t arraySize;
};

#endif