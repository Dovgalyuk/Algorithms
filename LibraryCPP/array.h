#ifndef ARRAY_H
#define ARRAY_H
#include <cstddef>

typedef int Data; // Тип данных

struct Array {
    Data* data; // Указатель
    size_t size; // Размер

    Array(size_t s); // Создать
    ~Array(); // Удалить
    size_t getSize() const; // Размер
    Data get(size_t index) const; // Получить
    void set(size_t index, Data value); // Установить
};

#endif

/*#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>

// Non-resizeable array

// Stores integer values inside
// Change it to desired type
typedef int Data;

struct Array;

// create array
Array *array_create(size_t size);

// delete array, free memory
void array_delete(Array *arr);

// returns specified array element
Data array_get(const Array *arr, size_t index);

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value);

// returns array size
size_t array_size(const Array *arr);

#endif
*/

/*#ifndef ARRAY_H
#define ARRAY_H

#include <stdexcept>

using namespace std;

class Array {
private:
    int* data;
    int size;

public:
    Array(int s) {
        if (s <= 0)
            throw invalid_argument("Размер должен быть положительным!");

        size = s;
        data = new int[size]; // Выделение памяти.
        for (int i = 0; i < size; i++)
            data[i] = 0;
    }

    ~Array() { delete[] data; } // Очистка памяти.

    int getSize() const { return size; }

    int& get(int index) {
        if (index < 0 || index >= size)
            throw out_of_range("Индекс вне границ!");

        return data[index];
    }

    const int& get(int index) const {
        if (index < 0 || index >= size)
            throw out_of_range("Индекс вне границ!");

        return data[index];
    }

    void set(int index, int value) { get(index) = value; }

    void fillFrom(const int* source) {
        for (int i = 0; i < size; i++)
            data[i] = source[i];
    }
};

#endif*/