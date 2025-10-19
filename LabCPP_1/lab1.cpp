/*
1.+	Реализовать контейнер - динамический массив array с неизменяемым размером (на любом из языков) 

2.+	Проверить работу соответствующей тестовой программы 

3.+	Написать две функции для обработки массива из следующих пунктов и вызвать их из функции main.

4.+	Прочитать целое число из файла, создать массив такой размерности и заполнить его числами из файла. 
    Определить количество элементов по модулю больших, чем максимальный. Вывести результат на экран. 

5.+	Прочитать целое число из файла, создать массив такой размерности и заполнить его числами из файла. 
    Сдвинуть элементы массива в указанном направлении (влево или вправо) и на указанное число шагов. 
    Освободившиеся ячейки заполнить нулями. Вывести результат на экран.

6.+	Добавить пример входных данных и описать тест в CMakeLists.txt, который запускает разработанную программу, использует входные данные и проверяет выходные на корректность.
*/


#include <iostream>
#include "array.h"
using namespace std;

Array *array_create_and_read(FILE *input)
{
    int n;
    if (fscanf(input, "%d", &n) != 1)
    {
        cerr << "Не удалось прочесть размер массива\n";
        return nullptr;
    }

    /* Create array */
    Array *arr = array_create(n);
    if (!arr)
    {
        cerr << "Ошибка при создании массива\n";
        return nullptr;
    }
    /* Read array data */
    for (int i = 0 ; i < n ; ++i)
    {
        int x = 0;
        if (fscanf(input, "%d", &x) != 1)
        {
            cerr << "Не удалось прочесть элемент массива на позиции " << i << "\n";
            array_delete(arr);
            return nullptr;
        }
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array *arr)
{
    if (!arr)
    {
        cerr << "Empty array in task1" << endl;
        return;
    }

    int maxNum = 0;
    int absCount = 0;
    int n = array_size(arr);

    for (int i = 0; i < n; i++) // Проходим первый раз, забираем максимально число
    {
        if (maxNum < array_get(arr, i))
        {
            maxNum = array_get(arr, i);
        }
    }
    for (int i = 0; i < n; i++) // Проходим второй раз, сравнивая модуль числа с максимальным
    {
        if (abs(array_get(arr, i)) > maxNum) // Если число по модулю больше максимального...
        {
            absCount++; // то +1 к кол-ву
        }
    }

    cout << "absCount = " << absCount << endl;
}

void task2(Array *arr, FILE *input)
{
    if (!arr)
    {
        cerr << "Empty array in task2" << endl;
        return;
    }

    int direction, step;
    int ret = fscanf(input, "%d %d", &direction, &step);
    if (ret != 2)
    {
        cerr << "Ошибка чтения направления и шага\n";
        return;
    }
    
    int n = array_size(arr);

    // cout << "1. <- \n2. ->" << endl;
    // cin >> direction;
    // direction = 1;
    // cout << "Input step: ";
    // cin >> step;
    // step = 2;
    cout << endl;
    
    switch (direction)
    {
    case 1: // Сдвиг влево
        for (int i = 0; i < n; i++)
        {
            if (i + step < n) // Проверка границы
                array_set(arr, i, array_get(arr, i + step)); // В пределах, забираем число ставим на место со сдвигом
            else
                array_set(arr, i, 0); // Если за пределами, меняем текущее на 0
        }
        break;

    case 2: // Сдвиг вправо
        for (int i = n; i-- > 0; )
        {
            if (i - step >= 0)
                array_set(arr, i, array_get(arr, i - step));
            else
                array_set(arr, i, 0);
        }
        break;

    default:
        cout << "Choose 1 or 2!" << endl;
        cout << endl;
        return;
    }

    cout << "Result array:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << array_get(arr, i) << " ";
    }
    cout << "\n" << endl;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "Using: " << argv[0] << " input.txt" << endl;
        return 1;
    }
    Array *arr = nullptr;

    FILE *input = fopen(argv[1], "r");
    if (input == nullptr)
    {
        cout << "Failed open input file" << endl;
        return 1;
    }

    arr = array_create_and_read(input);
    if (arr == nullptr)
    {
        fclose(input);
        return 1;
    }
    task1(arr);

    array_delete(arr);
    arr = nullptr;
    
    arr = array_create_and_read(input);
    if (arr == nullptr)
    {
        fclose(input);
        return 1;
    }
    task2(arr, input);

    array_delete(arr);
    arr = nullptr;

    fclose(input);

    return 0;
}