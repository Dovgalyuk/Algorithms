#include "Lab1CPP.h"

void TwoMin(Array* arr, ofstream& output)
{
    size_t size = array_size(arr);
    if (size < 2) return;

    Data a = array_get(arr, 0);
    Data b = array_get(arr, 1);

    Data min1, min2;
    if (a < b) { min1 = a; min2 = b; }
    else { min1 = b; min2 = a; }

    for (size_t i = 2; i < size; i++)
    {
        Data x = array_get(arr, i);
        if (x < min1)
        {
            min2 = min1;
            min1 = x;
        }
        else if (x < min2)
        {
            min2 = x;
        }
    }

    cout << min1 << " " << min2 << endl;
    output << min1 << " " << min2 << endl;
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

    Array* arr = array_create_and_read(input);
    if (!arr) {
        cout << "Ошибка: некорректный размер массива" << endl;
        output << "Ошибка: некорректный размер массива" << endl;
        return 1;
    }
    TwoMin(arr, output);
    array_delete(arr);

    return 0;
}