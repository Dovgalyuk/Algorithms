#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

Vector *vector_create(size_t initial_capacity, FFree f) {
    if (initial_capacity == 0) {
        initial_capacity = 1;
    }

    Vector* vec = malloc(sizeof(Vector));
    if (vec == NULL) {
        printf("Ошибка выделения памяти для структуры");
        return NULL;
    }

    vec->data = (Data *)malloc(initial_capacity * sizeof(Data));
    if (vec->data == NULL) {
        printf("Ошибка выделения памяти для массива");
        free(vec);
        return NULL;
    }

    vec->distruct = f;
    vec->size = 0;
    vec->capacity = initial_capacity;
    return vec;
}

void vector_delete(Vector *vector) {
    if (vector == NULL) {
        return;
    }
    if (vector->distruct != NULL) {
        for (size_t i = 0; i < vector->size; i++) {
            void* ptr = (void*)vector->data[i];
            vector->distruct(ptr);
        }
    }
    free(vector->data);
    free(vector);
}

Data vector_get(const Vector *vector, size_t index) {
    // Проверка на NULL
    if (vector == NULL) {
        printf("Ошибка: вектор пуст!\n");
        return NULL;
    }

    // Проверка корректности индекса
    if (index >= vector->size) {
        printf("Ошибка: индекс %zu вне границ (size: %zu)!\n", index, vector->size);
        return NULL;
    }

    return vector->data[index]; // Предполагаем, что вы правильно реализовали `data`
}

void vector_set(Vector *vector, size_t index, Data value) {
    if (vector == NULL) {
        printf("Ошибка: вектор пуст!\n");
        return;
    }

    if (index >= vector->capacity) {
        // Если индекс больше текущей емкости вектора, выполните resize
        vector_resize(vector, index + 1);
    }

    // Устанавливаем значение
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector) {
    return vector->size;
}

void vector_resize(Vector *vector, size_t new_size) {
    // Проверка на NULL
    if (vector == NULL) {
        printf("Ошибка: вектор пуст для resize!\n");
        return;
    }

    // Выделение новой памяти
    Data *new_data = (Data *)realloc(vector->data, new_size * sizeof(Data));
    if (new_data == NULL) {
        printf("Ошибка: память не выделена!\n");
        return;
    }
    
    vector->data = new_data;

    // Инициализация новых элементов значением по умолчанию
    for (size_t i = vector->size; i < new_size; ++i) {
        vector->data[i] = 0;  // Или любое другое значение по умолчанию, например, -1, если это имеет смысл
    }

    vector->size = new_size;  // Убедитесь, что размер вектора обновлен
}

void push_back(Vector *vector, Data value) {
    if (vector->size == vector->capacity) {
        vector_resize(vector, vector->capacity * 2);
        if (vector->data == NULL) {
            printf("Ошибка при выделении памяти в push_back\n");
            return;
        }
    }
    vector->data[vector->size++] = value;
}

Data pop_back(Vector *vector) {
    if (vector->size == 0) {
        printf("Ошибка: стек пуст!\n");
        return 0;
    }
    return vector->data[--vector->size];
}
