#include "lab1.h"

void task1(Array* arr, ofstream& output)
{
    size_t size = array_size(arr);
    if (size == 0) return;
    array_set(arr, 0, 0);
    for (size_t j = 1; j < size; j++)
    {
        size_t x = array_get(arr, j);
        if (x > 0)
        {
            size_t y = j;
            y += x;
            while (y<size) 
            {
                array_set(arr, y, 0);
                y += x;
            }
        }
    }
    for (size_t i = 0; i < size; i++)
    {
        if (array_get(arr, i) > 0)
        {
            size_t j = i;
            while (j > 0 && (array_get(arr, (j - 1)) == 0)) 
            {
                j--;
            }
            array_set(arr, j, array_get(arr, i));
            array_set(arr, i, 0);
        }
    }
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