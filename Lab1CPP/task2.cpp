#include <fstream>
#include <iostream>
#include "array.h"
using namespace std;

static Array* array_create_and_read(istream& input)
{
    int input_n = 0; // первое число в файле
    if (!(input >> input_n) || input_n < 0)
    {
        return nullptr;
    }

    Array* arr = array_create(static_cast<size_t>(input_n));

    for (int i = 0; i < input_n; ++i)
    {
        Data value = 0;
        if (!(input >> value)) // если в файле меньше чисел чем input_n
        {
            array_delete(arr);
            return nullptr;
        }
        array_set(arr, static_cast<size_t>(i), value);
    }
    return arr;
}

static void print_max_sum(const Array* arr)
{
    const size_t n = array_size(arr);

    if (n < 5)
    {
        cout << "размер массива должен быть больше 5\n";
        return;
    }

    long long current_sum = 0;
    for (size_t i = 0; i < 5; ++i) // по группам из 5 чисел
    {
        current_sum += array_get(arr, i);
    }

    long long max_sum = current_sum;
    size_t max_start = 0; // индекс группы с максимальной суммой 

    // метод скользящего окна (к текущей сумме прибавляет следующее число и вычитает число которое вышло из группы)
    for (size_t i = 1; i <= n - 5; ++i)
    {
        current_sum -= array_get(arr, i - 1);
        current_sum += array_get(arr, i + 4);

        if (current_sum > max_sum)
        {
            max_sum = current_sum;
            max_start = i;
        }
    }
    cout << max_sum << "\n";

    // вывод 5 элементов группы с максимальной суммрй
    for (size_t i = max_start; i < max_start + 5; ++i)
    {
        if (i != max_start)
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
        cerr << "не открыть файл\n";
        return 1;
    }

    Array* arr = array_create_and_read(input);

    if (arr == nullptr)
    {
        cerr << "некорректные данные для массива\n";
        return 1;
    }

    print_max_sum(arr);
    array_delete(arr);
    return 0;
}

// >> извлечение данных из файла