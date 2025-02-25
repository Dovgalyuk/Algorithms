#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <unordered_map>  
#include "array.h"  

using namespace std;

// Функция для поиска наибольшего отрезка нечётных чисел
void otrezokmassiva(Array* arr) {
    size_t size = array_size(arr);
    int count = 0; 
    int temp = 0;
    size_t start = 0;  
    size_t maxStart = 0;
    size_t maxEnd = 0;

    for (size_t i = 0; i < size; i++) {
        Data value = array_get(arr, i);
        if (value % 2 != 0) {
            if (temp == 0) start = i;
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

    // Проверка последнего отрезка
    if (count < temp) {
        count = temp;
        maxStart = start;
        maxEnd = size - 1;
    }

    cout << "\nНаибольшая длина отрезка нечётных чисел: " << count << endl;
    
    if (maxStart != 0 || maxEnd != 0) {
        cout << "Сам отрезок: ";
        for (size_t i = maxStart; i <= maxEnd; i++) {
            cout << array_get(arr, i);
            if (i < maxEnd) cout << ", ";
        }
        cout << endl;
    }
}

// Функция для поиска элементов, встречающихся ровно два раза
void povtorelevemt(Array* arr) {
    size_t size = array_size(arr);
    std::unordered_map<Data, int> countMap;  

    
    for (size_t i = 0; i < size; i++) {
        Data value = array_get(arr, i);
        countMap[value]++;
    }

    // Вывод элементов, которые повторяются 2 раза
    cout << "Элементы, которые повторяются 2 раза: ";
    for (const auto& pair : countMap) {
        if (pair.second == 2) { 
            cout << pair.first << " ";
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

    // Открытие файла
    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cerr << "Ошибка: не удалось открыть файл " << argv[1] << endl;
        return 1;
    }

    // Чтение размера массива
    size_t size;
    inputFile >> size;

    // Создание и заполнение массива
    Array* array = array_create(size);
    srand(static_cast<unsigned int>(time(0)));

    cout << "Сгенерированные числа: ";
    for (size_t i = 0; i < size; i++) {
        Data value = 1 + rand() % 50;
        array_set(array, i, value);
        cout << value;
        if (i < size - 1) cout << ", ";
    }
    cout << endl;

    // Обработка массива
    otrezokmassiva(array);
    povtorelevemt(array);

    // Освобождение памяти
    array_delete(array);
    return 0;
}