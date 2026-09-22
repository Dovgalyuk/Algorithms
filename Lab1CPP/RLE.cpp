#include "Lab1CPP.h"

void RLE(Array* arr, ofstream& output)
{
    size_t size = array_size(arr);
    if (size == 0) return;

    Data current = array_get(arr, 0);
    size_t count = 1;

    for (size_t i = 1; i < size; i++)
    {
        Data x = array_get(arr, i);
        if (x == current)
        {
            count++;
        }
        else
        {
            cout << current << " " << count << " ";
            output << current << " " << count << " ";
            current = x;
            count = 1;
        }
    }
    cout << current << " " << count << endl;
    output << current << " " << count << endl;
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
    RLE(arr, output);
    array_delete(arr);

    return 0;
}