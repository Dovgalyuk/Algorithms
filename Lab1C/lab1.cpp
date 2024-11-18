#include <iostream>
#include <fstream>
#include <cmath> // Для abs()
using namespace std;


void printTwoDigitNumbers(int* array, int size);
void printThreeDigitNumbers(int* array, int size);
int sumBetweenMinAndMax(int* array, int size);

int main() {
    string filename = "input.txt"; 
    ifstream file(filename);

    if (!file) {
        cout << "Ошибка: файл " << filename << " не найден!" << endl;
        return 1;
    }

    int size;
    while (file >> size) {
        if (size <= 0) {
            cout << "Ошибка: размер массива должен быть положительным!" << endl;
            return 1;
        }

        int* array = new int[size];

       
        for (int i = 0; i < size; i++) {
            if (!(file >> array[i])) {
                cout << "Ошибка: недостаточно данных в файле!" << endl;
                delete[] array; 
                return 1;
            }
        }

   
        cout << "Двузначные числа: ";
        printTwoDigitNumbers(array, size);
        cout << endl;

        cout << "Трёхзначные числа: ";
        printThreeDigitNumbers(array, size);
        cout << endl;

   
        int sum = sumBetweenMinAndMax(array, size);
        cout << "Сумма между минимальным и максимальным: " << sum << endl;
        cout << endl;

        delete[] array; 
    }

    file.close();
    return 0;
}


void printTwoDigitNumbers(int* array, int size) {
    for (int i = 0; i < size; i++) {
        if (abs(array[i]) >= 10 && abs(array[i]) <= 99) {
            cout << array[i] << " ";
        }
    }
}


void printThreeDigitNumbers(int* array, int size) {
    for (int i = 0; i < size; i++) {
        if (abs(array[i]) >= 100 && abs(array[i]) <= 999) {
            cout << array[i] << " ";
        }
    }
}


int sumBetweenMinAndMax(int* array, int size) {
    int minIndex = 0, maxIndex = 0;


    for (int i = 1; i < size; i++) {
        if (array[i] < array[minIndex]) minIndex = i;
        if (array[i] > array[maxIndex]) maxIndex = i;
    }

   
    if (abs(minIndex - maxIndex) <= 1) {
        return 0;
    }

    
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
