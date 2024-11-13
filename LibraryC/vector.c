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
    Vector* vec = (Vector*)malloc(sizeof(Vector));
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
            void* ptr = /*(void*)*/vector->data[i];
            vector->distruct(ptr);
        }
    }
    // Освобождаем память под массив данных и сам вектор
    free(vector->data);
    free(vector);
}

// Функция для получения элемента вектора по индексу
Data vector_get(const Vector *vector, size_t index) {
    // Проверяем, не равен ли вектор NULL
    if (vector == NULL) {
        fprintf(stderr, "Ошибка: вектор пуст!\n");
        return NULL;
    }

    // Проверяем, не превышает ли индекс размер вектора
    if (index >= vector->size) {
        fprintf(stderr, "Ошибка: индекс %zu вне границ (size: %zu)!\n", index, vector->size);
        return NULL;
    }

    // Возвращаем элемент по индексу
    return vector->data[index];
}

// Функция для установки значения элемента вектора по индексу
void vector_set(Vector *vector, size_t index, Data value) {
    // Проверяем, не равен ли вектор NULL
    if (vector == NULL) {
        fprintf(stderr, "Ошибка: вектор пуст!\n");
        return;
    }

    // Если индекс превышает ёмкость, изменяем размер вектора
    if (index >= vector->capacity) {
        vector_resize(vector, index + 1);
    }

    // Обновляем размер вектора, если индекс больше текущего размера
    if (index >= vector->size) {
        vector->size = index + 1; 
    }

    // Устанавливаем значение элемента по индексу
    vector->data[index] = value;
}

// Функция для получения текущего размера вектора
size_t vector_size(const Vector *vector) {
    return vector ? vector->size : 0;
}

// Функция для изменения размера вектора
// void vector_resize(Vector *v, size_t new_size) {
//     if (new_size == v->size) return;

//     if (new_size == 0) { // Если новый размер 0, освобождаем память
//         free(v->data);
//         v->data = NULL;
//     } else {
//         Data *new_data = (Data *)malloc(new_size * sizeof(Data));
//         if (!new_data) {
//             fprintf(stderr, "Ошибка выделения памяти\n");
//             return;
//         }

//         size_t copy_size = (new_size < v->size) ? new_size : v->size;
//         memcpy(new_data, v->data, copy_size * sizeof(Data));

//         if (new_size > v->size) { // Инициализация новых элементов NULL
//             memset(new_data + copy_size, 0, (new_size - copy_size) * sizeof(Data));
//         }

//         free(v->data);
//         v->data = new_data;
//     }
//     v->size = new_size;
// }
void vector_resize(Vector *v, size_t new_size) {
    if (v == NULL) return; 
    if (new_size == v->size) return;

    if (new_size == 0) { // Если новый размер 0, освобождаем память
        if (v->data) {
            free(v->data);
            v->data = NULL;
        }
        v->size = 0;
        v->capacity = 0;
    } else if (new_size < v->size) {
        v->size = new_size;
    } else {
        if (new_size > v->capacity) {
            size_t new_capacity = v->capacity > 0 ? v->capacity * 2 : 1; 
            while (new_capacity < new_size) { // Увеличиваем емкость до ближайшего размера
                new_capacity *= 2;
            }
            Data *new_data = (Data *)malloc(new_capacity * sizeof(Data));
            if (!new_data) {
                fprintf(stderr, "Ошибка выделения памяти\n");
                return;
            }
            // Копируем данные и инициализируем новые элементы
            if (v->data) {
                memcpy(new_data, v->data, v->size * sizeof(Data));
                free(v->data);
            }
            v->data = new_data;
            v->capacity = new_capacity;  // Обновляем емкость
        }
        v->size = new_size;
    }
}

// Функция для добавления элемента в конец вектора
void push_back(Vector *vector, Data value) {
    // Если вектор заполнен, увеличиваем его ёмкость
    if (vector == NULL) {
        printf("Ошибка: вектор пуст при добавлении элемента\n");
        return;
    }

    if (vector->size == vector->capacity) {
        vector_resize(vector, vector->capacity * 2);
        // Проверяем, выделена ли память успешно
        if (vector->data == NULL) {
            printf("Ошибка при выделении памяти в push_back\n");
            return;
        }
    }
    // Добавляем значение в конец вектора
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
