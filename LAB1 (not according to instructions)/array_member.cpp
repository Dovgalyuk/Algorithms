#include "array_member.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <set>

using namespace std;

int array_member::set_data()
{
    int number;
    cin >> number;
    return number;
}
void array_member::get_data(array_member* current_array_member)
{
    cout << current_array_member->data;
}
int array_member::randomize(int number_length)
{
    // вектор - алфавит
    vector <int> numbers = { 1,2,3,4,5,6,7,8,9 };
    // результирующий вектор
    vector <int> numbers_gen;

    int amount_of_numbers = 8;

    int result = 0;

    if (number_length > 1)
    {
        for (int i = 0; i < number_length; i++)
        {
            /*
                на первой позиции ноль стоять не может, тк он будет незначимым, то после прохождения
                первой генерации цифры просиходит добавление нуля в алфавит
            */
            if (i == 1)
            {
                amount_of_numbers++;
                numbers.push_back(0);
            }

            numbers_gen.push_back(numbers[rand() % amount_of_numbers]);
        }
    }
    else if (number_length == 1 || number_length == 0)
    {
        numbers_gen.push_back(0);
        amount_of_numbers++;

        return numbers[rand() % amount_of_numbers];
    }

    for (int i = 0; i < number_length; i++)
        result += pow(10, (number_length - i - 1)) * numbers_gen[i];

    return result;
}
void array_member::retail(array_member* current_array_member)
{
    current_array_member->tail_of_array = current_array_member->pointer_to_next->tail_of_array;

    if (current_array_member->pointer_to_previous != nullptr)
        retail(current_array_member->pointer_to_previous);
}

array_member::array_member()
{
    this->data = 0;

    pointer_to_next = nullptr;
    pointer_to_previous = nullptr;

    head_of_array = nullptr;
    tail_of_array = nullptr;
}

void array_member::create_array_member(array_member* currernt_array_member, int additional_information)
{
    // размер массива
    additional_information--;

    // проверка того, нужно ли ещё создавать элементы массива
    if (additional_information > 0)
    {
        // создание нового элемента списка
        array_member* pointer_to_next = new array_member;

        // распределение укзателя
        pointer_to_next->pointer_to_previous = currernt_array_member;

        if (currernt_array_member->pointer_to_previous == nullptr)
            currernt_array_member->head_of_array = currernt_array_member;
        else
            currernt_array_member->head_of_array = currernt_array_member->pointer_to_previous->head_of_array;

        currernt_array_member->pointer_to_next = pointer_to_next;
        pointer_to_next->tail_of_array = pointer_to_next;

        // рекурсивный вывод функции
        create_array_member(pointer_to_next, additional_information);
    }
    else
        retail(currernt_array_member->pointer_to_previous);
}
void array_member::print_array(array_member* current_array_member)
{
    cout << current_array_member->data << " ";

    if (current_array_member->pointer_to_next != nullptr)
        print_array(current_array_member->pointer_to_next);
    else
        cout << endl;
}
// удалить использование размера массива
void array_member::rnd_fill_array(array_member* current_array_member, int input_array_size)
{
    current_array_member->data = randomize(randomize(1));

    input_array_size--;

    if (current_array_member->pointer_to_next != nullptr)
        rnd_fill_array(current_array_member->pointer_to_next, input_array_size);
}
//дописать функцию удаления массива
void array_member::delete_array(array_member* current_array_member)
{
    if (current_array_member->pointer_to_next != nullptr)
    {
        array_member* pointer_to_next = current_array_member->pointer_to_next;

        delete current_array_member;

        delete_array(pointer_to_next);
    }
    else
        delete current_array_member;

}

int array_member::array_processing_1(array_member* current_array_member, int iterator, int &result)
{
    if (iterator % 2 == 0)
        result += current_array_member->data;
    else
        result -= current_array_member->data;

    iterator++;

    if (current_array_member->pointer_to_next != nullptr)
        array_processing_1(current_array_member->pointer_to_next, iterator, result);
    else
        return result;
}
// добавить проверку наличия элемента в сете
void array_member::array_processing_2(array_member* current_array_member, std::set<int>& numbers_wout_repeat)
{
    numbers_wout_repeat.insert(current_array_member->data);

    if (current_array_member->pointer_to_next != nullptr)
        array_processing_2(current_array_member->pointer_to_next, numbers_wout_repeat);
    else
        for (auto i : numbers_wout_repeat)
            cout << i << " ";
}