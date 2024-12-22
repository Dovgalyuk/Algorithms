#include "vector.h"
#include <iostream>
#include <vector>

using namespace std;

// Определение структуры Vector с использованием стандартного вектора STL
struct Vector {
    vector<int> data;  // Стандартный вектор для хранения данных
};

// Создание нового экземпляра структуры Vector
Vector* vector_create() {
    return new Vector;
}

// Удаление структуры Vector и освобождение памяти
void vector_delete(Vector* vector) {
    delete vector;
}

// Получение значения из вектора по индексу
int vector_get(const Vector* vector, size_t index) {
    if (index < vector->data.size()) { // Проверяем, что индекс в пределах массива
        return vector->data[index];  // Возвращаем элемент по индексу
    } else {
        cerr << "Ошибка: индекс за пределами!" << endl;
        return -1;  // Возвращаем -1 в случае ошибки
    }
}

// Установка значения в вектор по индексу
void vector_set(Vector* vector, size_t index, int value) {
    if (index < vector->data.size()) { // Проверяем, что индекс допустим
        vector->data[index] = value;  // Устанавливаем значение по индексу
    } else {
        cerr << "Ошибка: индекс за пределами!" << endl;
    }
}

// Получение текущего размера вектора
size_t vector_size(const Vector* vector) {
    return vector->data.size();  // Возвращаем размер вектора
}

// Изменение размера вектора
void vector_resize(Vector* vector, size_t size) {
    vector->data.resize(size);  // Изменяем размер вектора, добавляя или удаляя элементы
}
