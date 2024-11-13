#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

Vector *vector_create(size_t initial_capacity, FFree f) {
    // Устанавливаем минимальную ёмкость вектора в 1, если передана 0
    if (initial_capacity == 0) {
        initial_capacity = 1;
    }

    // Выделяем память под структуру вектора и массив данных
    Vector *vec = malloc(sizeof(Vector));
    if (!vec || !(vec->data = malloc(initial_capacity * sizeof(Data)))) {
        free(vec); // Освобождаем память, если не удалось выделить
        perror("Ошибка выделения памяти");
        return NULL;
    }

    vec->distruct = f;
    vec->size = 0;
    vec->capacity = initial_capacity;
    return vec;
}

// Функция для освобождения памяти, занимаемой вектором
void vector_delete(Vector *vector) {
    if (!vector) return;

    if (vector->distruct) {
        for (size_t i = 0; i < vector->size; ++i) {
            vector->distruct(vector->data[i]);
        }
    }
    free(vector->data);
    free(vector);
}

// Функция для получения элемента вектора по индексу
Data vector_get(const Vector *vector, size_t index) {
    if (!vector || index >= vector->size) {
        fprintf(stderr, "Ошибка: недопустимый доступ к вектору!\n");
        return NULL;
    }
    return vector->data[index];
}

// Функция для установки значения элемента вектора по индексу
void vector_set(Vector *vector, size_t index, Data value) {
    // Проверяем, не равен ли вектор NULL
    if (!vector) {
        fprintf(stderr, "Ошибка: вектор пуст!\n");
        return;
    }

    // Если индекс превышает ёмкость, изменяем размер вектора и обновляем размер
    if (index >= vector->capacity || index >= vector->size) {
        vector_resize(vector, index + 1);  // Увеличиваем размер, если это необходимо
        vector->size = index + 1; // Обновляем размер вектора
    }

    // Устанавливаем значение элемента по индексу
    vector->data[index] = value;
}

// Функция для получения текущего размера вектора
size_t vector_size(const Vector *vector) {
    return vector->size;
}

// Функция для изменения размера вектора
void vector_resize(Vector *v, size_t new_size) {
    if (new_size == v->size) return;

    Data *new_data = realloc(v->data, new_size * sizeof(Data));
    if (!new_data) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return;
    }

    if (new_size > v->size) {
        for (size_t i = v->size; i < new_size; i++) {
            new_data[i] = NULL; // Инициализация только при увеличении
        }
    }

    v->data = new_data;
    v->size = new_size;
}

// Функция для добавления элемента в конец вектора
void push_back(Vector *vector, Data value) {
    if (vector->size == vector->capacity) {
        vector_resize(vector, vector->capacity * 2);
    }
    vector->data[vector->size++] = value;
}

// Функция для удаления последнего элемента из вектора
Data pop_back(Vector *vector) {
    if (vector->size == 0) {
        fprintf(stderr, "Ошибка: вектор пуст!\n");
        return NULL; // Возвращаем NULL для избежания неопределенного поведения
    }
    return vector->data[--vector->size];
}
