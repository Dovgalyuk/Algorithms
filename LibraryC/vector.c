#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vector.h"

// Функция для создания вектора с указанной начальной ёмкостью и функцией освобождения памяти
Vector *vector_create(size_t initial_capacity, FFree f) {
    // Устанавливаем минимальную ёмкость вектора в 1, если передана 0
    if (initial_capacity == 0) {
        initial_capacity = 1;
    }

    // Выделяем память под структуру вектора
    Vector* vec = (Vector *)malloc(sizeof(Vector));
    // Проверяем, успешно ли выделена память
    if (vec == NULL) {
        printf("Ошибка выделения памяти для структуры");
        return NULL;
    }

    // Выделяем память под массив данных вектора
    vec->data = (Data *)malloc(initial_capacity * sizeof(Data));
    // Проверяем успешность выделения памяти под массив
    if (vec->data == NULL) {
        printf("Ошибка выделения памяти для массива");
        free(vec);
        return NULL;
    }

    // Устанавливаем функцию освобождения данных, размер и ёмкость вектора
    vec->distruct = f;
    vec->size = 0;
    vec->capacity = initial_capacity;
    return vec;
}

// Функция для освобождения памяти, занимаемой вектором
void vector_delete(Vector *vector) {
    // Проверяем, передан ли NULL
    if (vector == NULL) {
        return;
    }
    // Если задана функция distruct, вызываем её для каждого элемента вектора
    if (vector->distruct != NULL) {
        for (size_t i = 0; i < vector->size; i++) {
            // if (vector->data[i] != NULL) {
            //     vector->distruct(vector->data[i]);  // А освобождайте только, если указатель корректный
            // }
            void* ptr = (void*)vector->data[i];
            vector->distruct(ptr);
        }
    }
    // Освобождаем память под массив данных и сам вектор
    free(vector->data);
    free(vector);
}

// Функция для получения элемента вектора по индексу
Data vector_get(const Vector *vector, size_t index) {
    if (vector == NULL || index >= vector->size) {
        return NULL;
    }
    // Возвращаем элемент по индексу
    return vector->data[index];
}

int vector_get_int(const Vector *vector, size_t index) {
    if (vector == NULL || index >= vector->size) {
        return -1; // Ошибка, возвращаем -1
    }
    
    int *value = (int *)vector_get(vector, index);
    return (value != NULL) ? *value : -1;
}

void vector_set(Vector *vector, size_t index, Data value) {
    // Проверяем, не равен ли вектор NULL
    if (vector == NULL) {
        fprintf(stderr, "Ошибка: вектор пуст!\n");
        return;
    }

    // Увеличиваем размер только если индекс больше текущего размера
    if (index >= vector->size) {
        // Увеличение размера вектора
        vector_resize(vector, index + 1);
    }

    // Если требуется, освобождаем старое значение, если оно существует и не NULL
    if (vector->distruct != NULL && vector->data[index] != NULL) {
        vector->distruct(vector->data[index]); // Освобождение старых данных
    }

    // Устанавливаем новое значение элемента по индексу
    vector->data[index] = value;
}

// Функция для получения текущего размера вектора
size_t vector_size(const Vector *vector) {
    return vector ? vector->size : 0;
}

void vector_resize(Vector *v, size_t new_size) {
    if (v == NULL) return; 

    // Если новый размер меньше или равен текущему, ничего не делаем
    if (new_size <= v->size) {
        v->size = new_size;
        return;
    }

    // Увеличиваем емкость
    if (new_size > v->capacity) {
        size_t new_capacity = (new_size > v->capacity) ? (v->capacity * 2) : v->capacity;  
        while (new_capacity < new_size) {
            new_capacity *= 2;
        }

        Data *new_data = (Data *)malloc(new_capacity * sizeof(Data));
        if (!new_data) {
            fprintf(stderr, "Ошибка выделения памяти\n");
            return; // Не удается изменить размер
        }

        if (v->data) {
            memcpy(new_data, v->data, v->size * sizeof(Data));
            free(v->data);
        }

        v->data = new_data;
        v->capacity = new_capacity;
    }
    v->size = new_size;
}

// Функция для добавления элемента в конец вектора
void push_back(Vector *vector, Data value) {
    // Если вектор заполнен, увеличиваем его ёмкость
    if (vector == NULL) {
        return;
    }

    if (vector->size == vector->capacity) {
        vector_resize(vector, vector->capacity * 2);
    }
    vector->data[vector->size++] = value;
}

// Функция для удаления последнего элемента из вектора
Data pop_back(Vector *vector) {
    // Проверяем, не пуст ли вектор
    if (vector == NULL || vector->size == 0) {
        printf("Ошибка: стек пуст!\n");
        return NULL;
    }
    // Возвращаем последний элемент и уменьшаем размер вектора
    return vector->data[--vector->size];
}
