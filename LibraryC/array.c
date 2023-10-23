#include <stdlib.h> 

typedef struct {
    int* data;
    size_t size;
} Array;

Array* array_create(size_t size) {
    Array* arr = (Array*)malloc(sizeof(Array));
    if (arr != NULL) {
        arr->data = (int*)malloc(size * sizeof(int));
        if (arr->data != NULL) {
            arr->size = size;
            return arr;
        } else {
            free(arr);
            return NULL;
        }
    } else {
        return NULL;
    }
}

void array_delete(Array* arr) {
    if (arr != NULL) {
        free(arr->data);
        free(arr);
    }
}

int array_get(const Array* arr, size_t index) {
    if (arr != NULL && index < arr->size) {
        return arr->data[index];
    } else {
        return 0;
    }
}

void array_set(Array* arr, size_t index, int value) {
    if (arr != NULL && index < arr->size) {
        arr->data[index] = value;
    }
}

size_t array_size(const Array* arr) {
    if (arr != NULL) {
        return arr->size;
    } else {
        return 0;
    }
}