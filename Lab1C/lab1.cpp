#include "array.h"
#include <iostream>

using namespace std;

void task1(Array *arr)
{
    size_t size = array_size(arr);

    size_t maxElement = array_get(arr, 0);//Инициализация максимального элемента первым элементом массива
    for (size_t i = 0; i < size; i += 2)//Начинаем с элемента с индексом 0 и идём по чётным индексам (+2)
    {
        size_t currentElement = array_get(arr, i);//Получение текущего элемента массива
        if (currentElement > maxElement)
        {
            maxElement = currentElement;//Новый максимальный элемент
        }
    }

    cout << "Максимальный элемент среди элементов с четным индексом: " << maxElement << endl;
}

void task2(Array* arr)
{
    size_t size = array_size(arr);
    cout << "Введите интервал [a,b]:";
    size_t a;
    size_t b;
    cin >> a >> b;

    size_t zero = 0; //Количество ненулевых элементов

    //Перемещение ненулевые элементов в начало массива
    for (size_t i = 0; i < size; ++i)
    {
        int currentElement = array_get(arr, i);

        //Проверка, находится ли элемент в интервале [a, b]
        if (currentElement < a || currentElement > b)
        {
            //Элемент не находится в интервале, устанавливаем его значение в 0
            array_set(arr, zero, size_t());
        }
        else
        {
            //Элемент находится в интервале, перемещаем его в начало массива
            array_set(arr, zero, currentElement);
            zero++;
        }
    }

    //Заполнение оставшихся позиций нулями
    for (size_t i = zero; i < size; ++i)
    {
        array_set(arr, i, size_t());
    }
}


void CreateArray(Array* arr) {
    size_t size = array_size(arr);
    for (size_t i = 0; i < size; i++)
        array_set(arr, i, rand());
}

int main()
{
    setlocale (LC_ALL,"ru");
    srand((unsigned int)time(NULL)); //Инициализация генератора случайных чисел
    Array* arr = nullptr;
    size_t size;

    //task1
    cout << "Введите размер массива: ";
    cin >> size;
    arr = array_create(size);
    CreateArray(arr);
    cout << "Сгенерированный массив: ";
    for (size_t i = 0; i < size; ++i)
    {
        cout << array_get(arr, i) << " ";
    }
    cout << endl;
    task1(arr);
    array_delete(arr);

    //task2
    cout << "Введите размер массива 2: ";
    cin >> size;
    arr = array_create(size);
    CreateArray(arr);
    cout << "Сгенерированный массив: ";
    for (size_t i = 0; i < size; ++i)
    {
        cout << array_get(arr, i) << " ";
    }
    cout << endl;

    task2(arr);
    // Выводим результат
    cout << "Изменённый массив: ";
    for (size_t i = 0; i < array_size(arr); ++i)
    {
        cout << array_get(arr, i) << " ";
    }
    cout << endl;
    array_delete(arr);
}
