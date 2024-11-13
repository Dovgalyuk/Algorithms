#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

// Функция для создания вектора с указанной начальной ёмкостью и функцией освобождения памяти
Vector *vector_create(size_t initial_capacity, FFree f) {
    // Устанавливаем минимальную ёмкость вектора в 1, если передана 0
    if (initial_capacity == 0) {
        initial_capacity = 1;
    }

    // Выделяем память под структуру вектора
    Vector* vec = malloc(sizeof(Vector));
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
    return vector->size;
}

// Функция для изменения размера вектора
void vector_resize(Vector *v, size_t new_size) {
       // Если новый размер равен текущему, ничего не делаем
       if (new_size == v->size) return; 

       // Выделяем память для нового массива данных
       Data *new_data = (Data *)malloc(new_size * sizeof(Data));
       // Проверяем успешность выделения памяти
       if (new_data == NULL) {
           fprintf(stderr, "Ошибка выделения памяти\n");
           return;
       }
       
       // Определяем размер копируемых данных (минимум между новым и текущим размером)
       size_t copy_size = (new_size < v->size) ? new_size : v->size;
       for (size_t i = 0; i < copy_size; i++) {
           new_data[i] = v->data[i]; // Копируем данные
       }

    //    // Инициализируем новые элементы NULL в новом массиве
    //    for (size_t i = copy_size; i < new_size; i++) {
    //        new_data[i] = NULL;
    //    }

       // Освобождаем старый массив данных и обновляем указатель на новый массив
       free(v->data);
       v->data = new_data;
       v->size = new_size; // Обновляем размер вектора
   }

// Функция для добавления элемента в конец вектора
void push_back(Vector *vector, Data value) {
    // Если вектор заполнен, увеличиваем его ёмкость
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
    if (vector->size == 0) {
        printf("Ошибка: стек пуст!\n");
        return 0;
    }
    // Возвращаем последний элемент и уменьшаем размер вектора
    return vector->data[--vector->size];
}
