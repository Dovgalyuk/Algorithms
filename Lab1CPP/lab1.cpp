#include <iostream>
#include <fstream>
#include "array.h"

Array *array_create_and_read(std::istream& input)
{
    size_t n;
    input >> n;

    /* Create array */
    Array *arr = array_create(n);
    /* Read array data */
    for (int i = 0 ; i < n ; ++i)
    {
        Data x;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}


/*Прочитать целое число из файла, создать массив такой размерности. 
Заполнить массив простыми числами, начиная с 2. Вывести массив на экран.*/
void task1(Array *arr) 
{
    int num = 2;
    for (size_t i = 0; i < array_size(arr); ++i)
    {
        while (true)
        {
            bool prime = true;
            for (int j = 2; j * j <= num; ++j)
            {
                if (num % j == 0)
                {
                    prime = false;
                    break;
                }
            }
            if (prime) break;
            ++num;
        }
        array_set(arr, i, num++);
    }

    for (size_t i = 0; i < array_size(arr); ++i)
    {
        std::cout << array_get(arr, i) << " ";
    }
    std::cout << "\n";

}

/*Прочитать целое число из файла, создать массив такой размерности и 
заполнить его числами из файла. Найти пять соседних элементов, 
сумма значений которых максимальна. Вывести результат на экран.*/
void task2(Array *arr)
{
    size_t n = array_size(arr);
    if (n < 5)
    {
        return;
    }

    int maxSum = 0;
    int currSum = 0;
    size_t indx = 0;

    for (size_t i = 0; i < 5; ++i)
        currSum += array_get(arr, i);
    maxSum = currSum;

    for (size_t i = 5; i < n; ++i)
    {
        currSum = currSum - array_get(arr, i - 5) + array_get(arr, i);
        if (currSum > maxSum)
        {
            maxSum = currSum;
            indx = i - 4;
        }
    }

    for (size_t i = indx; i < indx + 5; ++i)
    {
        std::cout << array_get(arr, i) << " ";
    }
    std::cout << "\n";
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input)
    {
        return 1;
    }

    Array* arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);

    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);

    return 0;
}
