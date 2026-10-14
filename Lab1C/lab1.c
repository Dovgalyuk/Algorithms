#include <stdio.h>
#include "array.h"

// Создание и заполнение массива
Array *array_create_and_read(FILE *input)
{
    int n;

    if (fscanf(input, "%d", &n) != 1 || n <= 0)
    {
        printf("Недопустимый размер массива\n");
        return NULL;
    }

    Array *arr = array_create(n, NULL);

    if (arr == NULL)
    {
        printf("Ошибка создания массива\n");
        return NULL;
    }

    for (int i = 0; i < n; ++i)
    {
        int x;

        if (fscanf(input, "%d", &x) != 1)
        {
            printf("Ошибка чтения элемента массива\n");
            array_delete(arr);
            return NULL;
        }

        array_set(arr, i, x);
    }

    return arr;
}

// Первое задание
void task1(Array *arr)
{
    (void)arr;
}

void task2(Array *arr)
{
    (void)arr;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Укажите имя файла\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");

    if (input == NULL)
    {
        printf("Не удалось открыть файл\n");
        return 1;
    }

    // Первое задание
    Array *arr = array_create_and_read(input);

    if (arr == NULL)
    {
        fclose(input);
        return 1;
    }

    task1(arr);
    array_delete(arr);

    // Возвращаемся в начало файла
    rewind(input);

    // Второе задание
    arr = array_create_and_read(input);

    if (arr == NULL)
    {
        fclose(input);
        return 1;
    }

    task2(arr);
    array_delete(arr);

    fclose(input);

    return 0;
}