#include "lab1.h"

void task2(Array* arr, ofstream& output)
{
    size_t size = array_size(arr);
    if (size == 0) return;
    int count = 1;
    int value = array_get(arr, 0);
    size_t i = 1;
    while (i < size)
    {
        if (array_get(arr, i) == value)
        {
            count++;
        }
        else
        {
            output << count << value;
            cout << count << value;
            count = 1;
            value = array_get(arr, i);
        }
        i++;
    }
    output << count << value;
    cout << count << value;
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

    Array* arr = array_create_and_read(input, false);
    if (!arr) {
        cout << "Ошибка: некорректный размер массива" << endl;
        output << "Ошибка: некорректный размер массива" << endl;
        return 1;
    }
    task2(arr, output);
    array_delete(arr);

    return 0;
}