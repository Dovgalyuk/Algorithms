#include "vector.h"
#include <iostream>
#include <vector>

using namespace std;

struct Vector {
    vector<int> data;  // Стандартный вектор для хранения данных
};

Vector* vector_create() {
    return new Vector;
}

void vector_delete(Vector* vector) {
    delete vector;
}

int vector_get(const Vector* vector, size_t index) {
    if (index < vector->data.size()) {
        return vector->data[index];  // Возвращаем элемент по индексу
    } else {
        cerr << "Ошибка: индекс за пределами!" << endl;
        return -1;  // Ошибка
    }
}

void vector_set(Vector* vector, size_t index, int value) {
    if (index < vector->data.size()) {
        vector->data[index] = value;  // Устанавливаем значение по индексу
    } else {
        cerr << "Ошибка: индекс за пределами!" << endl;
    }
}

size_t vector_size(const Vector* vector) {
    return vector->data.size();  // Возвращаем размер вектора
}

void vector_resize(Vector* vector, size_t size) {
    vector->data.resize(size);  // Изменяем размер вектора
}
