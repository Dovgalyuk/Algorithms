#include "array.h"
#include <iostream>

using namespace std;

void task1(Array *arr)
{
    int m, n;
    cin >> m >> n; 

    size_t size = array_size(arr);
    bool decrease = true; 

    
    for (size_t i = 0; i < size; i++)
    {
        int value = array_get(arr, i);

        // Если флаг установлен в true, уменьшаем элемент на m, иначе увеличиваем на n
        //использовал логику того что элементы с нечетными номерами  и  нечетные элементы идут друг за другом
        if (decrease)
        {
            array_set(arr, i, value - m);
        }
        else
        {
            array_set(arr, i, value + n);
        }

        decrease = !decrease;
    }
}

void task2(Array *arr)
{
    size_t size = array_size(arr); 
//лямбда функция для проверки делится ли элемент на другие элементы
    auto is_divisible = [&](int num) {
        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size; j++)
            {
                if (i != j)
                {
                    int current = array_get(arr, i);
                    int other = array_get(arr, j);
                    if (other != 0 && current % other == 0)
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    };

    for (size_t i = 0; i < size; i++)
    {
        int current = array_get(arr, i);
        if (is_divisible(current))
        {
            cout << current << " ";
        }
    }
}


void CreateArray(Array* arr) {
    size_t size = array_size(arr);
    for (size_t i = 0; i < size; i++)
        array_set(arr, i, rand());
}


int main()
{
    Array *arr = NULL;
     size_t size;


    cin >> size;
    arr = array_create(size);
    CreateArray(arr);
    task1(arr);
    array_delete(arr);


   cin >> size;
    arr = array_create(size);
    CreateArray(arr);
    task2(arr);
    array_delete(arr);
}
