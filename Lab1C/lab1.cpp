#include <iostream>
#include <fstream>
#include <cmath> // Для abs()
using namespace std;

// Объявляем функции
void printTwoDigitNumbers(int* array, int size);
void printThreeDigitNumbers(int* array, int size);
int sumBetweenMinAndMax(int* array, int size);

int main() {
    int size;
    cout << "Введите размер массива: ";
    cin >> size;

    if (size <= 0) {
        cout << "Ошибка: размер массива должен быть положительным!" << endl;
        return 1;
    }

    int* array = new int[size];

    string filename;
    cout << "Введите имя файла: ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cout << "Ошибка: файл не найден!" << endl;
        delete[] array; // Освобождаем память
        return 1;
    }

    for (int i = 0; i < size; i++) {
        if (!(file >> array[i])) {
            cout << "Ошибка: недостаточно данных в файле!" << endl;
            delete[] array; // Освобождаем память
            return 1;
        }
    }
    file.close();

    // Печать двузначных и трёхзначных чисел
    cout << "Двузначные числа: ";
    printTwoDigitNumbers(array, size);
    cout << endl;

    cout << "Трёхзначные числа: ";
    printThreeDigitNumbers(array, size);
    cout << endl;

    // Считаем сумму между минимальным и максимальным
    int sum = sumBetweenMinAndMax(array, size);
    cout << "Сумма между минимальным и максимальным: " << sum << endl;

    delete[] array; // Освобождаем память
    return 0;
}

// Функция для вывода двузначных чисел
void printTwoDigitNumbers(int* array, int size) {
    for (int i = 0; i < size; i++) {
        if (abs(array[i]) >= 10 && abs(array[i]) <= 99) {
            cout << array[i] << " ";
        }
    }
}

// Функция для вывода трёхзначных чисел
void printThreeDigitNumbers(int* array, int size) {
    for (int i = 0; i < size; i++) {
        if (abs(array[i]) >= 100 && abs(array[i]) <= 999) {
            cout << array[i] << " ";
        }
    }
}

// Функция для подсчёта суммы между минимальным и максимальным
int sumBetweenMinAndMax(int* array, int size) {
    int minIndex = 0, maxIndex = 0;

    // Находим минимальный и максимальный элементы
    for (int i = 1; i < size; i++) {
        if (array[i] < array[minIndex]) minIndex = i;
        if (array[i] > array[maxIndex]) maxIndex = i;
    }

    // Если минимальный и максимальный рядом — возвращаем 0
    if (abs(minIndex - maxIndex) <= 1) {
        return 0;
    }

    // Считаем сумму между минимальным и максимальным
    int sum = 0;
    if (minIndex < maxIndex) {
        for (int i = minIndex + 1; i < maxIndex; i++) {
            sum += array[i];
        }
    } else {
        for (int i = maxIndex + 1; i < minIndex; i++) {
            sum += array[i];
        }
    }
    return sum;
}
