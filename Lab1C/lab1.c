#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "../LibraryC/array.h"

int count_greater_than_max(Array* arr) {
    if (arr->size == 0) return 0;
    
    int max_val = arr->data[0];
    for (size_t i = 1; i < arr->size; i++) {
        if (arr->data[i] > max_val) {
            max_val = arr->data[i];
        }
    }
    
    int count = 0;
    for (size_t i = 0; i < arr->size; i++) {
        if (abs(arr->data[i]) > max_val) {
            count++;
        }
    }
    return count;
}

void find_max_sum_five(Array* arr, int* start_index, int* max_sum) {
    *max_sum = 0;
    *start_index = -1;
    
    if (arr->size < 5) return;
    
    for (size_t i = 0; i <= arr->size - 5; i++) {
        int sum = 0;
        for (size_t j = 0; j < 5; j++) {
            sum += arr->data[i + j];
        }
        
        if (sum > *max_sum || *start_index == -1) {
            *max_sum = sum;
            *start_index = i;
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    printf("Задача 4\n");
    FILE* file = fopen("input_test1.txt", "r");
    if (!file) {
        printf("Ошибка открытия файла для задачи 4\n");
        return 1;
    }
    
    int size;
    fscanf(file, "%d", &size);
    
    Array* arr1 = array_create(size);
    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &arr1->data[i]);
    }
    fclose(file);
    
    int count = count_greater_than_max(arr1);
    printf("Количество элементов по модулю больших, чем максимальный: %d\n", count);
    array_destroy(arr1);
    
    printf("\nЗадача 5\n");
    file = fopen("input_test2.txt", "r");
    if (!file) {
        printf("Ошибка открытия файла для задачи 5\n");
        return 1;
    }
    
    fscanf(file, "%d", &size);
    Array* arr2 = array_create(size);
    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &arr2->data[i]);
    }
    fclose(file);
    
    int start_index, max_sum;
    find_max_sum_five(arr2, &start_index, &max_sum);
    
    if (start_index != -1) {
        printf("Максимальная сумма 5 соседних элементов: %d\n", max_sum);
        printf("Начиная с индекса: %d\n", start_index);
        printf("Элементы: ");
        for (int i = 0; i < 5; i++) {
            printf("%d ", arr2->data[start_index + i]);
        }
        printf("\n");
    } else {
        printf("Массив слишком мал для 5 соседних элементов\n");
    }
    array_destroy(arr2);
    
    return 0;
}