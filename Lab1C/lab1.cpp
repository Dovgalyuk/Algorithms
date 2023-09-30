#include <iostream>
#include "array.h"
#include <time.h> 
#include <random>

using namespace std;

Array* create() {
    size_t size;
    Array* arr = NULL; // Создаем массив без заданного размера
    cout << "what about size of array? " << endl;
    while (true) {
        cin >> size; // Вводим размер массива

        if (cin.fail()) { // Если ввод не удался
            cout << "Incorrect input" << endl;
            cin.clear(); // Очищаем флаг ошибки
            cin.ignore(32767, '\n'); // Очищаем буфер ввода
        }
        else {            
            arr = array_create(size); // Создаем массив указанного размера
            for (size_t i = 0; i < size; i++) {
                int j = rand() % 2; // Генерируем случайное число: 0 или 1
                if (j == 0) {
                    array_set(arr, i, (rand() % 100) * -1); // Если число 0, то генерируем отрицательное число
                }
                else {
                    array_set(arr, i, (rand() % 100)); // Если число 1, то генерируем положительное число
                }
            }
        }
        break;
    }
    return arr; // Возвращаем созданный массив
}

void first(Array* arr) {
    size_t size = array_size(arr); // Получаем размер массива
    Data elem = 0;
    Data sum = 0;
    float ariph = 0;
    Data count = 0;
    for (size_t i = 0; i < size; i++) {
        elem = array_get(arr, i); // Получаем элемент массива по индексу
        sum += elem; // Суммируем все элементы массива
        count++; // Увеличиваем счетчик
    }

    ariph = ((float)sum / (float)count); // Вычисляем среднее арифметическое

    cout << "The arithmetic mean of this array" << endl << ariph << endl; // Выводим среднее арифметическое
    
}

void second(Array* arr) {
    size_t size = array_size(arr); // Получаем размер массива
    Data elem = 0;
    Data elemsec = 0;

    for (size_t i = 0; i < size; i++) {
        elem = array_get(arr, i); // Получаем элемент массива по индексу
        int count = 1;
        for (size_t j = 0; j < size; j++) {
            elemsec = array_get(arr, j); // Получаем второй элемент массива по индексу
            if (elem == elemsec && i != j) { // Если элементы равны, но индексы не совпадают
                count++; // Увеличиваем счетчик        
            }
        }
        if (count == 2) { // Если count равно 2, то элемент повторяется один раз
            cout << elem << " "; // Выводим элемент      
        }
        array_set(arr, i, -1000); // Заменяем элемент на -1000
    }
}


void print(const Array* arr) {
    size_t size = array_size(arr); // Получаем размер массива
    cout << "Look on your array: " << endl;
    for (size_t i = 0; i < size; i++) {
        cout << array_get(arr, i) << " "; // Выводим элементы массива
    }
    cout << endl;
}

int main()
{
    srand(time(NULL)); // Инициализируем генератор случайных чисел
    Array* arr = NULL;

    cout << "task1" << endl;
    arr = create(); // Создаем массив
    print(arr); // Выводим массив на экран
    first(arr); // Выполняем первое задание
    array_delete(arr); // Удаляем массив

    cout << "task2" << endl;
    arr = create(); // Создаем массив
    print(arr); // Выводим массив на экран
    second(arr); // Выполняем второе задание 
}