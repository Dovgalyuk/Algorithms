#include <stdio.h>
#include <iostream>

#include "array.h"

using namespace std;

void task1(Array* arr)
{
    int total_resistance = 0; //Переменная для хранения общего сопротивления

    for (int i = 0; i < array_size(arr); i++) //Перебор массива
    {
        total_resistance += array_get(arr, i); //Суммирование значений всех элемнтов массива
    }

    cout << "Total resistance = " << total_resistance << endl; //Вывод суммы
}

void print_array(Array* arr) //Функция для вывода массива в консоль
{
    for (int i = 0; i < array_size(arr); i++) //Перебор массива
    {
        cout << array_get(arr, i) << " "; //Вывод значения текущего элемента массива
    }
}

void input_array(Array* arr, int max_range_random, int min_range_random) //Функция для заполнения массива рандомными числа (рандомные числа в определенном диапазоне)
{
    for (int i = 0; i < array_size(arr); i++) //Перебор массива
    {
        array_set(arr, i, rand() % (max_range_random + 1 - min_range_random) + min_range_random); //Присваивание значения элементу массива
    }

    cout << "Created array: " << endl;
    print_array(arr); //Вывод созданного массива
    
}


void task2(Array* arr, int shift_direction, int number_elements_shift)
{
    int number_of_changes = number_elements_shift; //Переменная для хранения количества изменений в массиве

    if (shift_direction < 0 || shift_direction > 1) //Если при вводе числа, отвечающего за направление сдвига, введено число меньше 0 или больше 1 (выбрано некорректное направление сдвига)
    {
        cout << "You entered the shift direction incorrectly. No changes" << endl; //Вывод сообщения
        return; //Выход из функции

    }
    if (number_elements_shift >= array_size(arr)) //Если введено количество элементов для сдвига больше или равное размеру массива, то обнуление всего массива
    {
        cout << "The number of elements to shift is entered >= than the size of the array itself. All array elements are 0" << endl; //Вывод сообщения
        for (int i = 0; i < array_size(arr); i++) //Перебор массива
        {
            array_set(arr, i, 0); //Присваивание значения 0 текущему элементу
        }
        return; //Выход из функции
    }
    else if (number_elements_shift == 0) //Если введено количество элементов для сдвига равное 0, то массив не изменяется
    {
        cout << "You entered 0 for the number of shifts. No changes" << endl; //Вывод сообщения
        return; //Выход из функции

    }
    else if (shift_direction == 0) //Если выбран сдвиг вправо, то
    {
        for (int i = array_size(arr)-1; i > 0; i--) //Перебор массива с конца
        {
            if (number_of_changes > 0) //Если количество изменений массива больше 0, то
            {
                if (i >= number_elements_shift) //Если индекс текущего элемента больше или равен количеству элементов для сдвига, то
                {
                    cout << "i:" << i << ", number_elements_shift:" << number_elements_shift << ", number_of_changes" << number_of_changes << endl;
                    array_set(arr, i, array_get(arr, i - number_elements_shift)); //Присваивание значения текущему элементу, значения элемента, который нужно сдвинуть
                    array_set(arr, i - number_elements_shift, 0); //Присвативание значения 0 элементу, который перемещен в другое место
                }
                else
                {
                    array_set(arr, i, 0); //Если условие не выолняется, то присваивам значение 0 элементу массива
                }                

                cout << endl << "Modified array: " << endl;
                print_array(arr); //Вывод измененного массива
            }
            number_of_changes--; //Уменьшение счетчика количества изменений
        }        
    }
    else if (shift_direction == 1) //Если выбран сдвиг влево, то
    {
        for (int i = 0; i < array_size(arr) - 1; i++) //Перебор массива с начала
        {
            if (number_of_changes > 0) //Если количество изменений массива больше 0, то
            {
                if (i <= array_size(arr) - number_elements_shift - 1) //Если индекс текущего элемента меньше или равен размеру массива минус 1 и минус количеству элементов для сдвига, то
                {
                    array_set(arr, i, array_get(arr, i + number_elements_shift)); //Присваивание значения текущему элементу, значения элемента, который нужно сдвинуть
                    array_set(arr, i + number_elements_shift, 0); //Присвативание значения 0 элементу, который перемещен в другое место
                }
                else
                {
                    array_set(arr, i, 0); //Если условие не выолняется, то присваивам значение 0 элементу массива
                }

                cout << endl << "Modified array: " << endl;
                print_array(arr); //Вывод измененного массива
            }
            number_of_changes--; //Уменьшение счетчика количества изменений
        }
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

    int shift_direction, number_elements_shift; //Переменные для хранения направления сдвига и количества элементов для сдвига

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
