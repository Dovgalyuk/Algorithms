#include "lab1.h"

void task1(Array* arr, ofstream& output)
{
    size_t size = array_size(arr);
    if (size == 0) return;
    Array* temp_arr = array_create(size);
    for (size_t i = 0; i < size; i++)
    {
        array_set(temp_arr, i, 1);
    }
    array_set(temp_arr, 0, 0);
    for (size_t j = 1; j < size; j++)
    {
        if (array_get(temp_arr, j) == 1)
        {
            int x = array_get(arr, j);
            for (size_t i = j + 1; i < size; i++)
            {
                int y = array_get(arr, i);
                if (y % x == 0)
                {
                    array_set(temp_arr, i, 0);
                }
            }
        }
    }
    size_t index = 0;

    for (size_t i = 0; i < size; i++)
    {
        if (array_get(temp_arr, i) == 1)
        {
            int prime = array_get(arr, i);
            array_set(arr, index, prime);
            index++;
        }
    }
    for (size_t i = index; i < size; i++)
    {
        array_set(arr, i, 0);
    }
    array_delete(temp_arr);
    array_print(cout, arr);
    array_print(output, arr);
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        cout << "При использовании файла: " << argv[0] << " произошла ошибка, Вы не указали входной файл" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input.is_open()) {
        cout << "Ошибка открытия файла" << endl;
        return 1;
    }
    ofstream output;
    if (argc >= 3) {
        output.open(argv[2]);
    }
    else {
        output.open("output.txt");
    }
    if (!output.is_open()) {
        cout << "Ошибка создания выходного файла" << endl;
        return 1;
    }

    Array* arr = array_create_and_read(input, true);
    if (!arr) {
        cout << "Ошибка: некорректный размер массива" << endl;
        output << "Ошибка: некорректный размер массива" << endl;
        return 1;
    }
    task1(arr, output);
    array_delete(arr);

    return 0;
}