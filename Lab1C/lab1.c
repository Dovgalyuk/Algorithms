#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "array.h"

static void set_int(Array *arr, size_t i, int x)
{
    array_set(arr, i, (Data)(intptr_t)x);
}

static int get_int(const Array *arr, size_t i)
{
    return (int)(intptr_t)array_get(arr, i);
}

Array *array_create_and_read(FILE *input)
{
    int n;
    if (fscanf(input, "%d", &n) != 1) {
        fprintf(stderr, "Ошибка: не удалось прочитать размер массива\n");
        exit(EXIT_FAILURE);
    }
    Array *arr = array_create((size_t)n, NULL);
    for (int i = 0; i < n; i++) {
        int x;
        if (fscanf(input, "%d", &x) != 1) {
            fprintf(stderr, "Ошибка: не удалось прочитать элемент %d\n", i);
            exit(EXIT_FAILURE);
        }
        set_int(arr, (size_t)i, x);
    }
    return arr;
}

void task1(Array *arr)
{
    size_t n = array_size(arr);
    Array *positives = array_create(n, NULL);
    Array *negatives = array_create(n, NULL);

    size_t pos_count = 0, neg_count = 0;
    for (size_t i = 0; i < n; i++) {
        int val = get_int(arr, i);
        if (val > 0)      set_int(positives, pos_count++, val);
        else if (val < 0) set_int(negatives, neg_count++, val);
    }

    printf("--- Задание 1 ---\n");
    printf("Исходный массив: ");
    for (size_t i = 0; i < n; i++) printf("%d ", get_int(arr, i));
    printf("\n");

    printf("Положительные числа: ");
    for (size_t i = 0; i < pos_count; i++) printf("%d ", get_int(positives, i));
    printf("\n");

    printf("Отрицательные числа: ");
    for (size_t i = 0; i < neg_count; i++) printf("%d ", get_int(negatives, i));
    printf("\n\n");

    array_delete(positives);
    array_delete(negatives);
}

void task2(Array *arr)
{
    size_t n = array_size(arr);

    printf("--- Задание 2 ---\n");
    printf("Исходный массив: ");
    for (size_t i = 0; i < n; i++) printf("%d ", get_int(arr, i));
    printf("\n");

    printf("Элементы, которые не делятся ни на какой другой элемент: ");
    int found_any = 0;

    for (size_t i = 0; i < n; i++) {
        int current = get_int(arr, i);
        int is_divisible = 0;
        for (size_t j = 0; j < n; j++) {
            if (i == j) continue;
            int other = get_int(arr, j);
            if (other == 0) continue;
            if (current % other == 0) { is_divisible = 1; break; }
        }
        if (!is_divisible) { printf("%d ", current); found_any = 1; }
    }
    if (!found_any) printf("Таких элементов нет");
    printf("\n");
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Использование: %s <input_file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    FILE *input = fopen(argv[1], "r");
    if (!input) {
        fprintf(stderr, "Ошибка: не удалось открыть файл %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    Array *arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);

    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);

    fclose(input);
    return EXIT_SUCCESS;
}
