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

    vec->data = malloc(initial_capacity * sizeof(Data));
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
    if (vector == NULL || index >= vector->size) {
        printf("Ошибка: массив пуст или индекс выходит за пределы");
        return NULL;
    }

    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value) {
    if (vector == NULL || index >= vector->size) {
        printf("Ошибка: массив пуст или индекс вышел за пределы размера");
        return;
    }
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector) {
    return vector->size;
}

void vector_resize(Vector *vector, size_t new_size) {
    if (new_size < 0) {
        printf("Ошибка: новый размер не может быть отрицательным\n");
        return;
    }

    if (new_size == vector->size) {
        return;
    }

    if (new_size > vector->capacity) {
        Data *new_data = realloc(vector->data, new_size * sizeof(Data));
        if (new_data == NULL) {
            printf("Ошибка при выделении памяти в vector_resize\n");
            return;
        }
        vector->data = new_data;
        vector->capacity = new_size;
    }
    if (new_size < vector->size) {
        for (size_t i = new_size; i < vector->size; i++) {
            if (vector->distruct != NULL && vector->data[i] != NULL) {
                   vector->distruct(vector->data[i]);
            }
        }
    }
    vector->size = new_size;
    for (size_t j = vector->size; j < new_size; ++j) {
        vector->data[j] = NULL;
    }
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
