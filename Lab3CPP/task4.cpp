#include <cstdio>
#include "array.h"

// Максимально возможное значение элемента массива по условию задачи
const int kMaxValue = 1000;

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

// Определяет число, которое встречается в массиве чаще всего.
// Значения элементов лежат в диапазоне [0, kMaxValue], поэтому
// подсчёт количества вхождений каждого значения (counting sort
// style) выполняется за время O(N + kMaxValue), то есть O(N).
// При равном количестве вхождений выбирается меньшее число.
void task4(const Array *arr, FILE *output)
{
    size_t size = array_size(arr);

    int counts[kMaxValue + 1] = {0};

    for (size_t i = 0; i < size; ++i)
    {
        Data value = array_get(arr, i);
        ++counts[value];
    }

    int bestValue = 0;
    int bestCount = -1;
    for (int value = 0; value <= kMaxValue; ++value)
    {
        if (counts[value] > bestCount)
        {
            bestCount = counts[value];
            bestValue = value;
        }
    }

    std::fprintf(output, "%d\n", bestValue);
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
    task4(arr, output);
    array_delete(arr);

    std::fclose(input);
    std::fclose(output);
}
