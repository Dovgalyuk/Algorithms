#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vector.h"

// typedef struct Vector {
//     size_t size; // Текущий размер вектора
//     Data* data; // Указатель на массив данных
//     size_t capacity; // Общая ёмкость вектора
//     FFree* distruct; // Указатель на функцию distruct для освобождения данных
// } Vector;

// Функция для создания вектора с указанной начальной ёмкостью и функцией освобождения памяти
Vector *vector_create(FFree f) {

    size_t initial_capacity = 4;

    // Выделяем память под структуру вектора
    Vector* vec = (Vector *)malloc(sizeof(Vector));
    // Проверяем, успешно ли выделена память
    if (!vec) {
        fprintf(stderr, "Ошибка выделения памяти для структуры");
        return NULL;
    }

    // Выделяем память под массив данных вектора
    vec->data = (Data *)malloc(initial_capacity * sizeof(Data));
    // Проверяем успешность выделения памяти под массив
    if (!vec->data) {
        free(vec);
        fprintf(stderr, "Ошибка выделения памяти для массива");
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
        fprintf(stderr, "Ошибка удаления");
        return;
    }
    // Если задана функция distruct, вызываем её для каждого элемента вектора
    if (vector->distruct != NULL) {
        for (size_t i = 0; i < vector->size; i++) {
            void* ptr = (void*)vector->data[i];
            vector->distruct(ptr);
        }
        // free(vector);
        // return;
    }
    // Освобождаем память под массив данных и сам вектор
    free(vector->data);
    vector->data = NULL; // Чтобы избежать двойного освобождения
    vector->size = 0;    // Обнуляем размер
    vector->capacity = 0; // Обнуляем емкость
    free(vector);
}

// Функция для получения элемента вектора по индексу
Data vector_get(const Vector *vector, size_t index) {
    if (vector == NULL || index >= vector->size) {
        return NULL;
    }
    // Возвращаем элемент по индексу
    Data element = vector->data[index];

    // Если данные - это указатель, и мы хотим проверять их на NULL
    if (element == NULL) {
        return NULL; // Если элемент == NULL, значит данных нет
    }

    return element;
}

// Функция для установки значения элемента вектора по индексу
void vector_set(Vector *vector, size_t index, Data value) {
    // Проверяем, не равен ли вектор NULL
    if (vector == NULL) {
        fprintf(stderr, "Ошибка: вектор пуст!\n");
        return;
    }

    // Увеличиваем размер только если индекс больше текущего размера
    if (index >= vector->capacity) {
        // Увеличение размера вектора
        vector_resize(vector, index + 1);
        // if (vector->data == NULL) {
        //     fprintf(stderr, "Ошибка: не удалось изменить размер вектора!\n");
        //     return; // Не удалось изменить размер, выходим
        // }
    }
    if (index >= vector->size) {
        vector->size = index + 1;
    }

    if (vector->data[index] != NULL) {
        vector->distruct(vector->data[index]); // Освобождаем ранее выделенную память для этого индекса
    }

    // Устанавливаем значение элемента по индексу
    vector->data[index] = value;
}

// Функция для получения текущего размера вектора
size_t vector_size(const Vector *vector) {
    return vector->size;
    //return vector ? vector->size : 0;
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
        size_t new_capacity = (v->capacity == 0) ? 1 : v->capacity * 2;  
        while (new_capacity < new_size) {
            new_capacity *= 2;
        }
        
        Data *new_data = (Data *)malloc(new_capacity * sizeof(Data));
        if (new_data == NULL) {
            return; // Не удается изменить размер
        }
        if (v->data != NULL) {
            memcpy(new_data, v->data, v->size * sizeof(Data));
            free(v->data);
        } 
        // Инициализация новых элементов (от v->size до new_size)
        for (size_t i = v->size; i < new_capacity; ++i) {
            new_data[i] = NULL; // или другое значение по умолчанию
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

    if (vector->size >= vector->capacity) {
        vector_resize(vector, vector->size + 1);
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
