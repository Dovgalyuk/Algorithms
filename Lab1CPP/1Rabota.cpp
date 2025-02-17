#include <iostream>
#include <fstream>  // Для работы с файлами
#include <cstdlib> 
#include <ctime>   
#include <locale>  
using namespace std;

void otrezokmassiva(int arr[], int size) {
    int count = 0; // Максимальная длина отрезка нечётных чисел
    int temp = 0;  // Текущая длина отрезка нечётных чисел
    int start = -1; // Начало текущего отрезка
    int maxStart = -1; // Начало наибольшего отрезка
    int maxEnd = -1;   // Конец наибольшего отрезка

    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            if (temp == 0) {
                start = i; 
            }
            temp++;
        } else {
            if (count < temp) {
                count = temp;
                maxStart = start;
                maxEnd = i - 1; 
            }
            temp = 0; 
        }
    }

    // Проверяем последний отрезок, если массив заканчивается на нечётное число
    if (count < temp) {
        count = temp;
        maxStart = start;
        maxEnd = size - 1; 
    }

    cout << '\n' << "Наибольшая длина отрезка нечётных чисел: " << count << endl;

    if (maxStart != -1 && maxEnd != -1) {
        cout << "Сам отрезок: ";
        for (int i = maxStart; i <= maxEnd; i++) {
            cout << arr[i];
            if (i < maxEnd) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

void povtorelevemt(int arr[], int size) {
    cout << "Элементы, которые повторяются 2 раза: ";
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                cout << arr[i] << " ";
                break;
            }
        }
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    // Проверка аргументов командной строки
    if (argc < 2) {
        cerr << "Ошибка: укажите путь к файлу с входными данными." << endl;
        return 1;
    }

    // Открываем файл с входными данными
    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cerr << "Ошибка: не удалось открыть файл " << argv[1] << endl;
        return 1;
    }

    int size;
    inputFile >> size; // Читаем размер массива из файла

    int* array = new int[size];
    srand(static_cast<unsigned int>(time(0))); // Инициализация генератора случайных чисел

    cout << "Сгенерированные числа: ";
    for (int i = 0; i < size; i++) {
        array[i] = 1 + rand() % 50; // Генерация случайных чисел от 1 до 50
        cout << array[i];
        if (i < size - 1) {
            cout << ", ";
        }
    }
    cout << endl;

    otrezokmassiva(array, size); // Нахождение наибольшего отрезка нечётных чисел
    povtorelevemt(array, size);  // Поиск элементов, которые повторяются 2 раза

    delete[] array; // Освобождение памяти
    return 0;
}