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


void vector_set(Vector *vector, size_t index, Data value) {
    if (vector == NULL) {
        fprintf(stderr, "Ошибка: вектор пуст!\n");
        return;
    }

    if (index >= vector->capacity) {
        vector_resize(vector, index + 1);
    }

    if (index >= vector->size) {
        vector->size = index + 1; // Убедитесь, что представленный размер увеличен
    }

    vector->data[index] = value;
}

size_t vector_size(const Vector *vector) {
    return vector->size;
}

void vector_resize(Vector *v, size_t new_size) {
       if (new_size == v->size) return; // Нет изменений размера

       Data *new_data = (Data *)malloc(new_size * sizeof(Data));
       if (new_data == NULL) {
           fprintf(stderr, "Ошибка выделения памяти\n");
           return;
       }
       
       // Копирование существующих данных
       size_t copy_size = (new_size < v->size) ? new_size : v->size;
       for (size_t i = 0; i < copy_size; i++) {
           new_data[i] = v->data[i];
       }

       // Инициализация новых данных
       for (size_t i = copy_size; i < new_size; i++) {
           new_data[i] = NULL; // или какое-либо значение по умолчанию
       }

       free(v->data);
       v->data = new_data;
       v->size = new_size;
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
