// 1)Реализовать контейнер - динамический массив array с неизменяемым размером (на любом из языков)
// 2)Проверить работу соответствующей тестовой программы
// 3)Написать две функции для обработки массива из следующих пунктов и вызвать их из функции main.
// 4)Ввести целое число, создать массив такой размерности и заполнить его из файла. Нечетные элементы массива уменьшить на m, а элементы с нечетными номерами увеличить на n. m и n ввести из файла.
// 5)Ввести целое число, создать массив такой размерности и заполнить его из файла. В массиве найти элементы, которые не делятся ни на какой другой элемент массива.
// 6)Добавить пример входных данных и описать тест в CMakeLists.txt, который запускает разработанную программу и использует входные данные.


#include <stdio.h>
#include <stdlib.h>
#include "array.h"

Array* array_create_and_read(FILE *input) {
    int n;
    scanf("%d", &n);

    /* Create array */
    Array *arr = array_create(n, NULL);

    /* Filling an Array */
    int c = 0;
    int cnt = 0;
    while (c != EOF && cnt != n) {
        fscanf(input, "%d", &c);
        array_set(arr, cnt, (Data)c);
        cnt++;
    }

    /* Read array data */
    for (int i = 0; i < n; i++) {
        int value = array_get(arr, i);
        printf("%d ", value);
    }
    printf("\n");

    return(arr);
} 

void task1(Array *arr, int n, int m)
{
    size_t arr_size = array_size(arr);
    if (arr_size == 0) {
        printf("Массив пуст.\n");
        return;
    }
    for (size_t i = 0; i < array_size(arr); i++) {
        int value = array_get(arr, i);
        if (value % 2 != 0) {
            value -= m;
        }
        if (i % 2 == 1) {
            value += n;
        }
        array_set(arr, i, (Data)value);
        printf("%d ", value);
    }
    printf("\n");
}

void task2(Array *arr)
{
    size_t arr_size = array_size(arr);
    if (arr_size == 0) {
        printf("Массив пуст.\n");
        return;
    }

    for (size_t i = 0; i < array_size(arr); i++) {
        int value_1 = array_get(arr, i);
        int is_divisible = 0;

        for (size_t j = 0; j < array_size(arr); j++) {
            if (i != j) {
                int value_2 = array_get(arr, j);
                if (value_1 % value_2 == 0) {
                    is_divisible = 1;
                    break; 
                }
            }         
        }
        if (!is_divisible)
            printf("%d ", value_1);  
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    int n, m;
    if (argc < 2) {
        printf("Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }
    fscanf(input, "%d%d", &n, &m);

    Array *arr = array_create_and_read(input);

    task1(arr, n, m);
    /* Removing an array */
    array_delete(arr);
    fclose(input);

    if (argc < 2) {
        printf("Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }
    FILE *input_2 = fopen(argv[1], "r");
    if (input_2 == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }
    /* Create another array here */
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);
    fclose(input_2);
}
