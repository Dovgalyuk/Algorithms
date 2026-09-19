#include <cstdio>
#include "array.h"

// Считывается размер массива из файла, создаётся массив и заполняется числами из файла.
Array *array_create_and_read(FILE *input)
{
    int n;
    fscanf(input, "%d", &n);
    // Создаётся массив нужного размера
    Array *arr = array_create(n);
    // Считываются элементы массива из файла
    for (int i = 0; i < n; ++i)
    {
        int x;
        fscanf(input, "%d", &x);
        array_set(arr, i, x);
    }
    return arr;
}

// Задание 1:
// Создаётся второй массив, в который сохраняются индексы чётных элементов
// первого массива. Результат выводится на экран.
void task1(Array *arr)
{
    size_t size = array_size(arr);

    // Сначала подсчитывается количество чётных элементов,
    // чтобы создать массив нужного размера
    size_t count = 0;
    for (size_t i = 0; i < size; ++i)
    {
        if (array_get(arr, i) % 2 == 0)
        {
            count++;
        }
    }

    // Создаётся второй массив для хранения индексов чётных элементов
    Array *result = array_create(count);

    // Заполняется массив индексами чётных элементов
    size_t pos = 0;
    for (size_t i = 0; i < size; ++i)
    {
        if (array_get(arr, i) % 2 == 0)
        {
            array_set(result, pos, (Data)i);
            pos++;
        }
    }

    // Выводятся индексы чётных элементов на экран
    for (size_t i = 0; i < array_size(result); ++i)
    {
        if (i > 0)
            printf(" ");
        printf("%d", array_get(result, i));
    }
    printf("\n");

    // Освобождается память второго массива
    array_delete(result);
}

int main(int argc, char **argv)
{
    // Открывается входной файл, имя которого передаётся аргументом командной строки
    FILE *input = fopen(argv[1], "r");
    // Считывается массив из файла
    Array *arr = array_create_and_read(input);
    // Выполняется задание 1
    task1(arr);
    // Освобождается память массива
    array_delete(arr);
    fclose(input);
    return 0;
}
