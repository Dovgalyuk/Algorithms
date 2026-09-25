#include <fstream>
#include <iostream>
#include "array.h"
using namespace std;

static void fill_natural_numbers(Array* arr)
{
    const size_t n = array_size(arr);
    for (size_t i = 0; i < n; ++i)
    {
        array_set(arr, i, static_cast<Data>(i + 1));
    }
}

static void sieve_eratosthenes(Array* arr)
{
    const size_t n = array_size(arr);
    if (n == 0)
    {
        return;
    }

    // число 1 (индекс 0) не является простым, замена на 0
    array_set(arr, 0, 0);

    // индекс i - 1 соответствует числу i
    for (size_t i = 2; i * i <= n; ++i)
    {
        if (array_get(arr, i - 1) != 0) // если число ещё не вычеркнуто
        {
            for (size_t j = i * i; j <= n; j += i) // по кратным числам i, которые заменяются на 0
            {
                array_set(arr, j - 1, 0);
            }
        }
    }

    // сдвиг простых чисел в начало 
    size_t write_index = 0; // индекс в какую ячейку записать число для сдвига

    for (size_t i = 0; i < n; ++i)
    {
        const Data value = array_get(arr, i); // i - индекс числа из массива value - число

        if (value != 0)
        {
            array_set(arr, write_index, value);
            ++write_index;
        }
    }

    // заполнение нулями до конца массива
    for (size_t i = write_index; i < n; ++i)
    {
        array_set(arr, i, 0);
    }
}

// вывод массива
static void print_array(const Array* arr)
{
    const size_t n = array_size(arr);
    for (size_t i = 0; i < n; ++i)
    {
        if (i != 0)
        {
            cout << " ";
        }

        cout << array_get(arr, i);
    }
    cout << "\n";
}

int main(int, char** argv)
{
    ifstream input(argv[1]);
    if (!input.is_open())
    {
        cerr << "не отрыть файл\n";
        return 1;
    }

    int input_n = 0;
    if (!(input >> input_n) || input_n < 0)
    {
        cerr << "некорректный размер массива\n";
        return 1;
    }

    Array* arr = array_create(static_cast<size_t>(input_n));

    fill_natural_numbers(arr);
    sieve_eratosthenes(arr);
    print_array(arr);

    array_delete(arr);
    return 0;
}