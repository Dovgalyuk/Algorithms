#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

// Функция для создания вектора с указанной начальной ёмкостью и функцией освобождения памяти
Vector *vector_create(size_t initial_capacity, FFree f) {
    if (initial_capacity == 0) {
        initial_capacity = 1;
    }

    Vector* vec = malloc(sizeof(Vector));
    if (vec == NULL) {
        fprintf(stderr, "Ошибка выделения памяти для структуры\n");
        return NULL;
    }

    vec->data = malloc(initial_capacity * sizeof(Data));
    if (vec->data == NULL) {
        fprintf(stderr, "Ошибка выделения памяти для массива\n");
        free(vec);
        return NULL;
    }

    vec->distruct = f;
    vec->size = 0;
    vec->capacity = initial_capacity;
    return vec;
}

// Функция для освобождения памяти, занимаемой вектором
void vector_delete(Vector *vector) {
    if (vector == NULL) return;
    if (vector->distruct != NULL) {
        for (size_t i = 0; i < vector->size; i++) {
            void* ptr = (void*)vector->data[i];
            vector->distruct(ptr);
        }
    }
    free(vector->data);
    free(vector);
}

// Функция для получения элемента вектора по индексу
Data vector_get(const Vector *vector, size_t index) {
    if (vector == NULL) {
        fprintf(stderr, "Ошибка: вектор пуст!\n");
        return NULL;
    }

    if (index >= vector->size) {
        fprintf(stderr, "Ошибка: индекс %zu вне границ (size: %zu)!\n", index, vector->size);
        return NULL;
    }

    return vector->data[index];
}

// Функция для установки значения элемента вектора по индексу
void vector_set(Vector *vector, size_t index, Data value) {
    if (vector == NULL) {
        fprintf(stderr, "Ошибка: вектор пуст!\n");
        return;
    }

    if (index >= vector->capacity) {
        // Увеличиваем ёмкость вектора
        size_t new_capacity = index + 1;
        // Увеличиваем ёмкость вдвое для упрощения дальнейшего роста
        while (new_capacity < vector->capacity) {
            new_capacity *= 2;
        }
        Data *new_data = realloc(vector->data, new_capacity * sizeof(Data));
        if (new_data == NULL) {
            fprintf(stderr, "Ошибка при реаллокации памяти\n");
            return;
        }
        vector->data = new_data;
        vector->capacity = new_capacity;
    }

    // Обновляем размер при необходимости
    if (index >= vector->size) {
        vector->size = index + 1;
    }

    vector->data[index] = value;
}

// Функция для получения текущего размера вектора
size_t vector_size(const Vector *vector) {
    return vector ? vector->size : 0;
}

// Функция для добавления элемента в конец вектора
void push_back(Vector *vector, Data value) {
    if (vector == NULL) return;
    if (vector->size == vector->capacity) {
        // Увеличиваем ёмкость вдвое
        size_t new_capacity = vector->capacity ? vector->capacity * 2 : 1;
        Data *new_data = realloc(vector->data, new_capacity * sizeof(Data));
        if (new_data == NULL) {
            fprintf(stderr, "Ошибка при выделении памяти в push_back\n");
            return;
        }
        vector->data = new_data;
        vector->capacity = new_capacity;
    }
    vector->data[vector->size++] = value; // Добавляем значение в конец вектора
}

// Функция для удаления последнего элемента из вектора
Data pop_back(Vector *vector) {
    if (vector == NULL || vector->size == 0) {
        fprintf(stderr, "Ошибка: стек пуст!\n");
        return NULL;
    }
    return vector->data[--vector->size];
}