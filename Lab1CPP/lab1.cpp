#include <cstdio>
#include <stdexcept>
#include "array.h"

Array* array_create_and_read(FILE* input);
void task1(const Array* arr);
void task2(const Array* arr);


int main(int argc, char* argv[])
{
    Array* arr = NULL;
    FILE* input = fopen(argv[1], "r");
    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);
    fclose(input);
    return 0;
}

Array* array_create_and_read(FILE* input)
{
    int n;
    if (!fscanf(input, "%d", &n)) throw std::invalid_argument("Failed to read size");
    if (n < 0) throw std::invalid_argument("Size out of range");
    /* Create array */
    Array* arr = array_create(n);
    /* Read array data */
    for (int i = 0; i < n; ++i)
    {
        int x;
        if (!(fscanf(input, "%d", &x))) throw std::invalid_argument("Failed to read number");
        array_set(arr, i, x);
    }

    return arr;
}

void task1(const Array* arr)
{
    int sum = 0;
    size_t size = array_size(arr);
    for (size_t index{ 0 }; index < size; ++index)
    {
        if (array_get(arr, index) <= 20)
        {
            sum += array_get(arr, index);
        }
    }
    printf("%d", sum);
}

void task2(const Array* arr)
{
    int flag;
    size_t size = array_size(arr);
    for (size_t index{ 0 }; index < size; ++index)
    {
        flag = 1;
        for (size_t index2{ 0 }; index2 < size; ++index2)
        {
            if ((index2 != index) && array_get(arr, index2) == 0) {
                flag = 0;
            }
            else if ((index2 != index) && (array_get(arr, index) % array_get(arr, index2) == 0)) {
                flag = 0;
            }
        }
        if (flag == 1)
        {
            printf("%d ", array_get(arr, index));
        }
    }
}