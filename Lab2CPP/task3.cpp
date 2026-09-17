#include <cstdio>
#include "array.h"

// Читает из файла целое число N, затем N чисел,
// создаёт массив нужного размера и заполняет его
Array *array_create_and_read(FILE *input)
{
    int n;
    std::fscanf(input, "%d", &n);
    Array *arr = array_create((size_t)n);
    for (int i = 0; i < n; ++i)
    {
        int x;
        std::fscanf(input, "%d", &x);
        array_set(arr, (size_t)i, x);
    }
    return arr;
}

// Находит количество элементов массива, значение которых больше
// среднего арифметического минимального и максимального элементов,
// и печатает их номера (индексы, начиная с 0) в файл output
void task3(const Array *arr, FILE *output)
{
    size_t size = array_size(arr);

    if (size == 0)
    {
        std::fprintf(output, "0\n\n");
        return;
    }

    Data minValue = array_get(arr, 0);
    Data maxValue = array_get(arr, 0);
    for (size_t i = 1; i < size; ++i)
    {
        Data value = array_get(arr, i);
        if (value < minValue)
            minValue = value;
        if (value > maxValue)
            maxValue = value;
    }

    double average = (minValue + maxValue) / 2.0;

    size_t count = 0;
    for (size_t i = 0; i < size; ++i)
    {
        if (array_get(arr, i) > average)
            ++count;
    }

    std::fprintf(output, "%zu\n", count);

    bool first = true;
    for (size_t i = 0; i < size; ++i)
    {
        if (array_get(arr, i) > average)
        {
            if (!first)
                std::fprintf(output, " ");
            std::fprintf(output, "%zu", i);
            first = false;
        }
    }
    std::fprintf(output, "\n");
}

int main(int argc, char **argv)
{
    if (argc < 3)
        return 1;

    FILE *input = std::fopen(argv[1], "r");
    if (!input)
        return 1;
    FILE *output = std::fopen(argv[2], "wb");
    if (!output)
    {
        std::fclose(input);
        return 1;
    }

    Array *arr = array_create_and_read(input);
    task3(arr, output);
    array_delete(arr);

    std::fclose(input);
    std::fclose(output);
}
