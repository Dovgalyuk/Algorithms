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

// Задание 2:
// Находятся элементы, которые встречаются в массиве ровно два раза.
// Используется массив-счётчик размером 1001 (числа от 0 до 1000).
// Алгоритм работает за время O(N).
void task2(Array *arr)
{
    size_t size = array_size(arr);

    // Создаётся массив-счётчик на 1001 элемент (индексы от 0 до 1000).
    // Каждый элемент count[i] хранит, сколько раз число i встретилось в массиве.
    Array *count = array_create(1001);

    // Все счётчики устанавливаются в ноль
    for (size_t i = 0; i < 1001; ++i)
    {
        array_set(count, i, 0);
    }

    // Подсчитывается количество вхождений каждого числа.
    // Для каждого элемента массива увеличивается соответствующий счётчик.
    for (size_t i = 0; i < size; ++i)
    {
        Data val = array_get(arr, i);
        Data old_count = array_get(count, val);
        array_set(count, val, old_count + 1);
    }

    // Выводятся числа, которые встречаются ровно два раза
    int first = 1;  // флаг для правильного вывода пробелов
    for (size_t i = 0; i < 1001; ++i)
    {
        if (array_get(count, i) == 2)
        {
            if (!first)
                printf(" ");
            printf("%d", (int)i);
            first = 0;
        }
    }
    printf("\n");

    // Освобождается память массива-счётчика
    array_delete(count);
}

int main(int argc, char **argv)
{
    // Открывается входной файл, имя которого передаётся аргументом командной строки
    FILE *input = fopen(argv[1], "r");
    // Считывается массив из файла
    Array *arr = array_create_and_read(input);
    // Выполняется задание 2
    task2(arr);
    // Освобождается память массива
    array_delete(arr);
    fclose(input);
    return 0;
}
