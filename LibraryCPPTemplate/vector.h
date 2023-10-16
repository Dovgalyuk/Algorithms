#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector()
    {
        vector_size = 0;
        max_size = 1;
        data = new Data[max_size];
    }

    // copy constructor
    // Vector(const Vector &a)
    // {
    //     // implement or disable this function
    // }

    // assignment operator
    // Vector &operator=(const Vector &a)
    // {
    //     // implement or disable this function
    //     return *this;
    // }

    // Deletes vector structure and internal data
    ~Vector()
    {
        delete[] data;
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const
    {
        if (vector_size <= index) {
            throw "Error: the index does not exist!";
        }
        return data[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        if (vector_size <= index) {
            throw "Error: the index does not exist!";
        }
        data[index] = value;
    }

    // Retrieves current vector size
    size_t size() const
    {
        return vector_size;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t size)
    {
        if (size <= max_size) {
            vector_size = size;
            return;
        }
        // Выделение памяти под расширенный массив
        size_t _max_size = size * 2;
        Data* tmp = new Data[_max_size];
        // Перенос элементов
        for (size_t i = 0; i < vector_size; i++) {
            tmp[i] = data[i];
        }
        // Удаление текущего массива, замена расширенным
        delete[] data;

        data = tmp;
        max_size = _max_size;
        vector_size = size;
    }

private:
    // private data should be here
    Data* data;
    size_t vector_size;
    size_t max_size;
};

#endif