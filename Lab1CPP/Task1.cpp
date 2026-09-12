#include "general.h"

void Task1(Array *arr) {
    size_t size = array_size(arr);

    double sumPos = 0, sumNeg = 0;
    int countPos = 0, countNeg = 0;

    for (size_t i = 0; i < size; i++) {
        int val = array_get(arr, i);

        if (val < 0) {
            countNeg++;
            sumNeg += val;
        } else if (val > 0) {
            countPos++;
            sumPos += val;
        }
    }

    if (countPos > 0)
        cout << "Среднее арифметическое положительных: " << sumPos / countPos << endl;
    else
        cout << "Положительных элементов нет" << endl;

    if (countNeg > 0)
        cout << "Среднее арифметическое отрицательных: " << sumNeg / countNeg << endl;
    else
        cout << "Отрицательных элементов нет" << endl;
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "Russian");

    if (argc < 2) {
        cout << "Входной файл не найден!!" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input.is_open()) {
        cout << "Ошибка открытия файла" << endl;
        return 1;
    }

    Array *arr = array_create_and_read(input);
    if (arr == nullptr) {
        cout << "Ошибка чтения массива" << endl;
        return 1;
    }

    Task1(arr);

    array_delete(arr);
    return 0;
}