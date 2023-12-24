#include "array.h"
#include <iostream>
#include <cstdlib> //для использования ф-и rand()
#include <ctime>

using namespace std;

void task1()
{
    setlocale(LC_ALL, "ru");
    int size;
    cout << "Введите размерность массива: ";
    cin >> size;

    Array* arr = array_create(size);//создание массива
    srand(time(0));//использ текущ время для инициализации рандома

    //заполнение массива рандом числами
    for (int i = 0; i < size; ++i) {
        array_set(arr, i, rand() % 101 - 50);//случайные числа от -50 до 50
    }

    cout << "Элементы массива: ";
    for (int i = 0; i < size; ++i) {
        cout << array_get(arr, i) << " ";
    }
    cout << endl;

    //среднее арифмет положительных чисел
    double countP = 0;
    double sumP = 0;
    for (int i = 0; i < size; ++i) {
        if (array_get(arr, i) > 0) {
            sumP += array_get(arr, i);
            ++countP;
        }
    }
    double resP;
    if (countP > 0) {
        resP = sumP / countP;
    }
    else {
        resP = 0;
    }
    cout << "Среднее арифметическое положительных элементов массива: " << resP << endl;

    //среднее арифмет отрицательных чисел
    double countN = 0;
    double sumN = 0;
    for (int i = 0; i < size; ++i) {
        if (array_get(arr, i) < 0) {
            sumN += array_get(arr, i);
            ++countN;
        }
    }
    double resN;
    if (countN > 0) {
        resN = sumN / countN;
    }
    else {
        resN = 0;
    }
    cout << "Среднее арифметическое отрицательных элементов массива: " << resN << endl;

    array_delete(arr);
}

void task2()
{
    size_t size;
    int dir, steps;

    cout << "Введите размерность массива: ";
    cin >> size;

    Array* arr = array_create(size);
    srand(time(0));

    for (size_t i = 0; i < size; ++i) {
        array_set(arr, i, rand() % 101); //заполняем случайными числами от 0 до 100
    }

    cout << "Элементы массива: ";
    for (size_t i = 0; i < size; ++i) {
        cout << array_get(arr, i) << " ";
    }
    cout << endl;

    cout << "Введите направление сдвига (0 - вправо, 1 - влево): ";
    cin >> dir;
    cout << "Введите количество шагов: ";
    cin >> steps;

    for (int step = 0; step < steps; ++step) {
        if (dir == 0) { //сдвиг вправо
            for (size_t i = size - 1; i > 0; --i) {
                array_set(arr, i, array_get(arr, i - 1));
            }
            array_set(arr, 0, 0); //заполнение первого эл нулем
        }
        else if (dir == 1) { //сдвиг влево
            for (size_t i = 0; i < size - 1; ++i) {
                array_set(arr, i, array_get(arr, i + 1));
            }
            array_set(arr, size - 1, 0); //заполнение последнего эл нулем
        }

        //выводим массив после каждого шага
        cout << "Шаг " << step + 1 << ": ";
        for (size_t i = 0; i < size; ++i) {
            cout << array_get(arr, i) << " ";
        }
        cout << endl;
    }

    array_delete(arr);
}

int main()
{
    setlocale(LC_ALL, "ru");
    int ex;
    cout << "Введите номер задания: ";
    cin >> ex;
    if (ex == 1) {
        task1();
    }
    else if (ex == 2) {
        task2();
    }
    else {
        cout << "Такого задания нет. " << endl;
    }

    return 0;
}