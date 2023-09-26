#include <stdio.h>
#include <iostream>
#include <ctime>

#include "array.h"

using namespace std;

void task1(Array* arr)
{
    double total_resistance = 0; //Переменная для хранения общего сопротивления резисторов

    for (size_t i = 0; i < array_size(arr); i++) //Перебор массива
    {
        total_resistance += 1 / double(array_get(arr, i)); //Суммирование значений обратных значениям массива
    }

    total_resistance = 1 / total_resistance; //Нахождение общего сопротивления

    cout << "Total resistance = " << total_resistance << endl; //Вывод общего сопротивления
}

void print_array(Array* arr) //Функция для вывода массива в консоль
{
    for (size_t i = 0; i < array_size(arr); i++) //Перебор массива
    {
        cout << array_get(arr, i) << " "; //Вывод значения текущего элемента массива
    }
}

void input_array(Array* arr, int max_range_random, int min_range_random) //Функция для заполнения массива рандомными числа (рандомные числа в определенном диапазоне)
{
    srand(time(0)); //Для корректной работы функции rand(). При старте программы "стартовое число" одно и тоже, этой функцие оно меняется

    for (size_t i = 0; i < array_size(arr); i++) //Перебор массива
    {
        array_set(arr, i, rand() % (max_range_random + 1 - min_range_random) + min_range_random); //Присваивание значения элементу массива
    }

    cout << "Created array: " << endl;
    print_array(arr); //Вывод созданного массива

}

void shift_right(Array* arr) //Функция сдвига массива вправо на один элемент
{
    for (size_t i = array_size(arr) - 1; i > 0; i--) //Перебор массива
    {
        array_set(arr, i, array_get(arr, i - 1)); //Сдвиг вправо всех элементов
    }
    array_set(arr, 0, 0); //Присваивание значению первого элемента значение 0
}
void shift_left(Array* arr) //Функция сдвига массива влево на один элемент
{
    for (size_t i = 0; i < array_size(arr) - 1; i++) //Перебор массива
    {
        array_set(arr, i, array_get(arr, i + 1)); //Сдвиг влево всех элементов
    }
    array_set(arr, array_size(arr) - 1, 0); //Присваивание значению первого элемента значение 0
}

void task2(Array* arr, int shift_direction, size_t number_elements_shift)
{
    if (number_elements_shift >= array_size(arr)) //Если введено количество элементов для сдвига больше или равное размеру массива, то обнуление всего массива
    {
        cout << "The number of elements to shift is entered >= than the size of the array itself. All array elements are 0" << endl; //Вывод сообщения
        for (size_t i = 0; i < array_size(arr); i++) //Перебор массива
        {
            array_set(arr, i, 0); //Присваивание значения 0 текущему элементу
        }
        return; //Выход из функции
    }
    if (number_elements_shift == 0) //Если введено количество элементов для сдвига равное 0, то массив не изменяется
    {
        cout << "You entered 0 for the number of shifts. No changes" << endl; //Вывод сообщения
        return; //Выход из функции

    }
    for (size_t i = 0; i < number_elements_shift; i++) //Выплнение сдвига введенное количство раз
    {
        if (!shift_direction) //Если выбран сдвиг вправо, то
        {
            shift_right(arr); //Вызов функции сдвига вправо
        }
        else
        {
            shift_left(arr); //Вызов функции сдвига влево
        }
        cout << endl << "Modified array: " << endl;
        print_array(arr); //Вывод измененного массива
    }
}

int main()
{
    size_t size_arr; //Переменная для ввода размера массива
    int max_range_random = 100, min_range_random = 1; //Переменные для хранения границ диапазона генерации случайных чисел

    cout << "Enter array size: ";
    cin >> size_arr; //Ввод размера массива

    if (cin.fail()) //Обработка некорректного ввода
    {
        cout << "Incorrect input." << endl;
        return 0;
    }

    Array* arr = NULL;

    /* Create array here */
    arr = array_create(size_arr); //Выделение памяти для массива (создание массива)
    input_array(arr, max_range_random, min_range_random); //Заполнение массива сулчайными числами

    task1(arr); //Выполнение первого задания (подсчет общего сопротивления)
    array_delete(arr); //Освобождение памяти (удаление массива)

    bool shift_direction; //Переменная для хранения направления сдвига
    size_t number_elements_shift; //Переменная для хранения количества элементов для сдвига

    cout << "Enter array size: ";
    cin >> size_arr; //Ввод размера массива
    cout << "Enter shift direction (0 (right) or 1 (left)): ";
    cin >> shift_direction; //Ввод направления сдвига
    cout << "Enter the number of elements to shift <= " << size_arr << ": ";
    cin >> number_elements_shift; //Ввод количества элементов для сдвига

    if (cin.fail()) //Обработка некорректного ввода
    {
        cout << "Incorrect input." << endl;
        return 0;
    }

    /* Create another array here */
    arr = array_create(size_arr); //Выделение памяти для массива (создание массива)
    input_array(arr, max_range_random, min_range_random); //Заполнение массива сулчайными числами

    task2(arr, shift_direction, number_elements_shift); //Выполнение второго задания (сдвиг массива)
    array_delete(arr); //Освобождение памяти (удаление массива)
}
