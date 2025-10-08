#include <stdio.h>
#include <locale.h>
#include "array.h"

Array* array_create_and_read(FILE* input)
{
    int n;
    if (fscanf(input, "%d", &n) != 1) return NULL;

    Array* arr = array_create(n, NULL);
    for (int i = 0; i < n; ++i) {
        int x;
        fscanf(input, "%d", &x);
        array_set(arr, i, x);
    }

    return arr;
}

void task1(Array* arr)
{
    int month_days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    int start = 0;

    printf("Осадки по месяцам:\n");
    for (int m = 0; m < 12; ++m) {
        int sum = 0;
        for (int i = 0; i < month_days[m] && start + i < array_size(arr); ++i) {
            sum += array_get(arr, start + i);
        }
        printf("%d ", sum);
        start += month_days[m];
    }
    printf("\n");
}

void task2(Array* arr)
{
    int a = 2, b = 5;
    int write_index = 0;
    int n = array_size(arr);

    for (int i = 0; i < n; ++i) {
        int val = array_get(arr, i);
        if (val < a || val > b) {
            array_set(arr, write_index++, val);
        }
    }
    while (write_index < n) {
        array_set(arr, write_index++, 0);
    }

    printf("Сжатый массив:\n");
    for (int i = 0; i < n; ++i) {
        printf("%d ", array_get(arr, i));
    }
    printf("\n");
}

int main(int argc, char** argv)
{
    setlocale(LC_ALL, ""); 

    if (argc < 2) {
        fprintf(stderr, "Ошибка: не указан файл ввода\n");
        return 1;
    }

    FILE* input = fopen(argv[1], "r");
    if (!input) {
        fprintf(stderr, "Не удалось открыть файл: %s\n", argv[1]);
        return 1;
    }

    Array* arr = array_create_and_read(input);
    fclose(input);

    if (!arr) {
        fprintf(stderr, "Ошибка чтения массива\n");
        return 1;
    }

    task1(arr);
    array_delete(arr);

    input = fopen(argv[1], "r");
    arr = array_create_and_read(input);
    fclose(input);

    if (!arr) {
        fprintf(stderr, "Ошибка чтения массива во второй задаче\n");
        return 1;
    }

    task2(arr);
    array_delete(arr);

    return 0;
}
