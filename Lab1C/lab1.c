/*
    Реализовать контейнер - динамический массив array с неизменяемым размером (на любом из языков)
    Проверить работу соответствующей тестовой программы
    Написать две функции для обработки массива из следующих пунктов и вызвать их из функции main.
    Ввести целое число с клавиатуры, создать массив такой размерности и заполнить его случайными числами. Найти количество элементов, значение которых больше среднего арифметического минимального и максимального элементов массива, и напечатать их номера.
    Ввести целое число с клавиатуры, создать массив такой размерности и заполнить его случайными числами. Найти пять соседних элементов, сумма значений которых максимальна.
    Добавить пример входных данных и описать тест в CMakeLists.txt, который запускает разработанную программу и использует входные данные.
*/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "array.h"

Array *array_create_and_read(FILE *input) {
    int n;
    fscanf(input, "%d", &n);
    
    /* Create array */
    Array *arr = array_create(n, NULL);
    
    /* Read array data */
    for (int i = 0; i < n; ++i) {
        int *x = malloc(sizeof(int)); 
        fscanf(input, "%d", x);
        array_set(arr, i, x); 
    }
    return arr;
}


void array_random_sum(FILE *input_2) {
    int n;
    fscanf(input_2, "%d", &n);

    Array *arr = array_create(n, NULL);

    for (int i = 0; i < n; ++i) {
        int *x = malloc(sizeof(int)); 
        *x = rand() % 10 + 1;
        array_set(arr, i, x); 
    }

    int max = *(int *)array_get(arr, 0);
    
    for (int i = 1; i < n; i++) {
        if (*(int *)array_get(arr, i) > max) {
            max = *(int *)array_get(arr, i);
        }
    }
    
    int min = *(int *)array_get(arr, 0);
    for (int i = 1; i < n; i++) {
        if (*(int *)array_get(arr, i) < min) { 
            min = *(int *)array_get(arr, i);
        }
    }
    
    int sum = (max + min) * 0.5;
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        if (*(int *)array_get(arr, i) > sum) {
            count += 1;
            printf("a[%d] - %d\n", i, (*(int *)array_get(arr, i)));
        }
    }
    printf("количество - %d\n", count);
    
    
    for (int i = 0; i < n; i++) {
        free(array_get(arr, i)); 
    }
    
}


void array_neighboring_sum(FILE *input_3)
{
    int n;
    fscanf(input_3, "%d", &n);
    
    if (n < 5) {
        printf("Недостаточно элементов для вычисления суммы.\n");
        return;
    }

    Array *arr = array_create(n, NULL);

    for (int i = 0; i < n; i++) {
        int *x = malloc(sizeof(int)); 
        *x = rand() % 10 + 1;
        array_set(arr, i, x); 
    }
    
    for (int i = 0; i < n; i++) {
      printf("a[%d] - %d\n", i, (*(int *)array_get(arr, i)));
    }
    
    int max_sum = 0;
    
/*  было так := for (int i = 0; i <= n - 5; i ++){ int sum = (*(int *)array_get(arr, i) + 
(*(int *)array_get(arr, i + 1) +(*(int *)array_get(arr, i + 2) + (*(int *)array_get(arr, i + 3) + 
(*(int *)array_get(arr, i + 4)))))); но читаемость данного блока вызывала сомнения */
      
    for (int i = 0; i < n - 5; i ++){
       int sum = 0;
       for (int j = 0; j < 5; j ++){
          sum += *(int *)array_get(arr,i + j);
        }
    if (max_sum < sum ){
        max_sum = sum;
    }
  }
    
    printf("Максимальная сумма пяти соседних элементов - %d",max_sum);
    
     for (int i = 0; i < n; i++) {
        free(array_get(arr, i));    
    }
}


int main(/*int argc, char **argv*/) 
{
    srand(time(NULL));
    
    
    FILE *input = fopen("../Lab1C/input.txt", "r");
    if (input == NULL) {
        perror("Ошибка открытия файла input.txt");
        return 1; 
    }

    Array *arr = array_create_and_read(input);
    if (arr == NULL) {
        fprintf(stderr, "Ошибка при чтении массива\n");
        fclose(input); 
        return 1;
    }
    
   
    FILE *input_2 = fopen("../Lab1C/input_2.txt", "r");
    if (input_2 == NULL) {
        perror("Ошибка открытия файла input.txt");
        return 1; 
    }
    
    array_random_sum(input_2); 
    
    
    FILE *input_3 = fopen("../Lab1C/input_3.txt", "r");
    if (input_3 == NULL) {
        perror("Ошибка открытия файла input.txt");
        return 1; 
    }
    
    array_neighboring_sum(input_3);
    

    fclose(input); 
    fclose(input_2);
    fclose(input_3);

    array_delete(arr); 

    return 0;
}

   

