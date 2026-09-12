#include "general.h"

void Task2(Array *arr) {
    size_t size = array_size(arr);
    const int maximum = 1000;
    int count[maximum + 1] = {0};

    for (size_t i = 0; i < size; i++) {
        int val = array_get(arr, i);
        if (val < 0 || val > maximum) {
            cerr << "Число вне диапазона" << endl;
            exit(1);
        }
        count[val]++;
    }

    cout << "Элементы массива, которые не повторяются: ";
    bool flag = false;
    for (int i = 0; i <= maximum; i++) {
        if (count[i] == 1) {
            if (flag) {
                cout << ", ";
            }
            cout << i;
            flag = true;
        }
    }
    if (!flag) {
        cout << "Таких элементов нет!";
    }
    cout << endl;
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

    Task2(arr);

    array_delete(arr);
    return 0;
}