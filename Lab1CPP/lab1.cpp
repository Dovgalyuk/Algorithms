#include "lab1.h"

Array *array_create_and_read(FILE *input)
{
    int n;
    if(fscanf(input, "%d", &n) != 1)
        return nullptr;
    /* Create array */
    Array *arr = array_create(n);
    /* Read array data */
    for (int i = 0 ; i < n ; ++i)
    {
        int x;
        if(fscanf(input, "%d", &x) != 1)
        {
            array_delete(arr);
            return nullptr;
        }
        array_set(arr, i, x);
    }
    return arr;
}

// Ввести целое число, создать массив такой размерности и заполнить его из файла.
// Из всех положительных элементов вычесть элемент с номером k1, из остальных — элемент с номером k2. k1 и k2 ввести из файла.
Array* task1(Array *arr, FILE *input)
{
    int k1, k2;
    if(fscanf(input, "%d %d", &k1, &k2) != 2)
        return nullptr;

    Array* ans = array_create(array_size(arr));
    for(size_t i = 0; i < array_size(ans); i++)
    {
        int x = array_get(arr,i);
        if(x > 0)
            array_set(ans,i,(x - k1));
        else
            array_set(ans,i,(x - k2));
    }
    
    array_delete(arr);
    return ans;
}

// Ввести целое число, создать массив такой размерности и заполнить его из файла.
// В массиве найти элементы, которые не делятся ни на какой другой элемент массива.
Array* task2(Array *arr)
{
    size_t ansSize = 0;

    for(size_t i = 0; i < array_size(arr); i++)
    {
        size_t j = 0;
        for(; j < array_size(arr); j++)
        {
            if(i != j && array_get(arr,i) % array_get(arr, j) == 0)
                break;
        }
        
        if(j == array_size(arr))
            ansSize++;
    }

    Array* ans = array_create(ansSize);
    size_t index = 0;

    for(size_t i = 0; i < array_size(arr); i++)
    {
        size_t j = 0;
        for(; j < array_size(arr); j++)
        {
            if(i != j && array_get(arr,i) % array_get(arr, j) == 0)
                break;
        }
        
        if(j == array_size(arr))
        {
            array_set(ans, index, array_get(arr, i));
            index++;
        }
    }
    array_delete(arr);
    return ans;
}