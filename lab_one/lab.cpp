#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include "../LibraryCPP/array.h"

using namespace std;

Array *array_create_and_read(ifstream &input) {

    //считывание размера array
    size_t size;
    input >> size;

    //создание array
    Array *arr = array_create(size);
    if (!arr) return nullptr;

    //заполнение array числами из файла
    for (size_t i = 0; i < size; i++) {
        int num;
        if (!(input >> num)) {
            cerr << "Error input" << endl;
            array_delete(arr);
            return nullptr;
        }
        else array_set(arr, i, num);
    }
    
    //возвращем массив чисел
    return arr;
}

void task1(Array *arr, size_t size) {
    int n = 0;
    int summ = 0;
    for (size_t i = 0; i != size; i++) {
        if (array_get(arr, i) > 10) {
            n++;
            summ += array_get(arr, i);
        }
    } 

    if (n > 0) {
        cout << "Task number one: " << (double)summ / n << endl;
    }
    else cout << "Task number one has no answer" << endl;
}

void task2(Array *arr, size_t size, ifstream &input) {

    size_t a, b;
    size_t n = 0;
    input >> a;
    input >> b;
    for (size_t i = 0; i < size-n; i++) {
        if (array_get(arr, i) >= a && array_get(arr, i) <= b) {
            n++;
            for (size_t j = i; j < (size-n); j++) {
                array_set(arr, j, array_get(arr, (j+1)));
            }
            i--;

        }
    }
    for (size_t i = size - n; i < size; i++) {
        array_set(arr, i, 0);
    }


    //вывод массива-результата
    cout << "Task number two: ";
    for (size_t i = 0; i < (size-1); i++) {
        cout << array_get(arr, i) << " ";
    }
    cout << array_get(arr, size-1);
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        cerr << "usage: " << argv[0] << " <file_path>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    /*if (!input) {
        cout << "opening error" <<  endl;
        return 1;
    }*/

    Array *arr = array_create_and_read(input);
    task1(arr, array_size(arr));
    task2(arr, array_size(arr), input);
    array_delete(arr);

    input.close();
}

