#include <iostream>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <set>

#include "array_member.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "russian");
    srand(time(NULL));

    // создание стартового объекта для работы списка
    array_member* start_array_member = new array_member;

    // сет для хранения чисел без повтора
    set <int> numbers_wout_repeat;

    int size_of_array = 0;

    int result_array_processing_1 = 0;

    cout << "Введите размер массива:";
    cin >> size_of_array;
    cout << endl;

    start_array_member->create_array_member(start_array_member, size_of_array);
    start_array_member->rnd_fill_array(start_array_member, size_of_array);

    cout << "Случайно заполненный массив: ";
    start_array_member->print_array(start_array_member);
    cout << endl;

    cout << "Знакопеременная сумма элементов: ";
    cout << start_array_member->array_processing_1(start_array_member, 0, result_array_processing_1) << endl;

    cout << "Элементы, которые встречаются в массиве только один раз: ";
    start_array_member->array_processing_2(start_array_member, numbers_wout_repeat);
    cout << endl;

    start_array_member->delete_array(start_array_member);
}