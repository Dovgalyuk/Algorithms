#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

int main(int argc, char* argv[])
{
    const char* filename = "input.txt";

    if (argc > 1)
    {
        filename = argv[1];
    }

    ifstream input(filename);

    if (!input.is_open())
    {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return 1;
    }

    // Считываем размер массива
    size_t n;
    input >> n;

    // Создаём массив
    Array* arr = array_create(n);

    // Массив для подсчёта количества вхождений
    // Числа находятся в диапазоне от 0 до 1000
    int count[1001] = {};

    // Заполняем массив и одновременно считаем вхождения
    for (size_t i = 0; i < n; i++)
    {
        int value;
        input >> value;

        array_set(arr, i, value);
        count[value]++;
    }

    input.close();

    // Выводим элементы, которые встречаются только один раз
    cout << "Элементы, встречающиеся только один раз:" << endl;

    for (size_t i = 0; i < n; i++)
    {
        int value = array_get(arr, i);

        if (count[value] == 1)
        {
            cout << value << " ";
        }
    }

    cout << endl;

    // Освобождаем память
    array_delete(arr);

    return 0;
}