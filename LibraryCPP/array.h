#pragma once
#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H
#include <iostream>
using namespace std;

template <typename Data> class Array
{
public:
    // create array
    Array(size_t size)
    {
        elem = new Data[size];
        sized = size;

    }

    // delete array, free memory
    ~Array()
    {
        delete[] elem;
    }

    // returns specified array element
    Data get(size_t index) const
    {
        return elem[index];
    }

    void sort() const {
        int tmp = 0;
        for (int i = 0; i < sized; i++) {
            for (int j = (sized - 1); j >= (i + 1); j--) {
                if (elem[j] < elem[j - 1]) {
                    tmp = elem[j];
                    elem[j] = elem[j - 1];
                    elem[j - 1] = tmp;
                }
            }
        }
    }

    int min() const {
        int min = elem[0];
        for (int i = 0; i < sized; i++) {
            if (min > elem[i]) {
                min = elem[i];
            }
        }
        return min;
    }

    int max() const {
        int max = elem[0];
        for (int i = 0; i < sized; i++) {
            if (max < elem[i]) {
                max = elem[i];
            }
        }
        return max;
    }

    void output() const {
        for (int i = 0; i < sized; i++) {
            cout << elem[i] << " ";
        }
    }

    // sets the specified array element to the value
    void set(size_t index, Data value)
    {
        elem[index] = value;
    }

    // returns array size
    size_t size() const
    {

        return sized;
    }

private:
    Data* elem;
    size_t sized;
    // private data should be here
};
#endif