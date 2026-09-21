#include <iostream>
#include <fstream>
#include "array.h"
#include "lab1.h"

using namespace std;
void task1(Array* arr, ofstream& output)
{
    size_t size = array_size(arr);
    if (size == 0) return;

    for (size_t i = 0; i < size / 2; i++){
        Data zero_el = array_get(arr, i);
        Data end_el = array_get(arr, size - 1 - i);
        array_set(arr, i, end_el);
        array_set(arr, size - 1 - i, zero_el);
    }
    array_print(output, arr);
}

int main(int argc, char** argv)
{
    if (argc < 2){
        cout << "Не указан входной файл" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input.is_open()){
        cout << "Ошибка открытия входного файла" << endl;
        return 1;
    }

    ofstream output;
    if (argc >= 3)
        output.open(argv[2]);
    else
        output.open("output.txt");

    if (!output.is_open()){
        cout << "Ошибка создания выходного файла" << endl;
        return 1;
    }

    Array* arr = array_create_and_read(input);
    if (!arr){
        cout << "Ошибка неправильный размер массива" << endl;
        return 1;
    }
    task1(arr, output);
    array_delete(arr);

    return 0;
}