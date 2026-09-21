#include <iostream>
#include <fstream>
#include "array.h"
#include "lab1.h"

using namespace std;

void task2(Array* arr, int a, int b, ofstream& output)
{
    size_t size = array_size(arr);
    size_t write = 0;
    for (size_t read = 0; read < size; read++){
        Data value = array_get(arr, read);
        if (value < a || value > b){
            array_set(arr, write, value);
            write++;
        }
    }

    for (size_t i = write; i < size; i++){
        array_set(arr, i, 0);
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
        cout << "Ошибка: некорректный размер массива" << endl;
        return 1;
    }

    int a;
    int b;
    if (!(input >> a >> b)){
        cout << "Ошибка: не удалось прочитать границы интервала" << endl;
        array_delete(arr);
        return 1;
    }
    task2(arr, a, b, output);
    array_delete(arr);

    return 0;
}