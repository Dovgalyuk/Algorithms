#include <iostream> // Подключаем библиотеку для работы с вводом и выводом
#include <fstream>  // Подключаем библиотеку для работы с файлами
#include "array.h"  // Подключаем заголовочный файл с описанием структуры массива

using namespace std; // Используем пространство имен std для упрощения записи

// Функция для заполнения массива из файла
void fill_array_from_file(Array* arr, const string& filename) {
    ifstream file(filename); // Открываем файл с именем filename для чтения
    if (!file.is_open()) { // Проверяем, удалось ли открыть файл
        throw runtime_error("Unable to open file: " + filename); // Если файл не открыт, выбрасываем исключение
    }
    for (size_t i = 0; i < array_size(arr); ++i) { // Проходим по всем элементам массива
        int value; // Переменная для хранения значения из файла
        file >> value; // Считываем значение из файла
        array_set(arr, i, value); // Записываем считанное значение в массив
    }
    file.close(); // Закрываем файл
}

// Функция для вычисления суммы и произведения всех элементов массива
void process_array_sum_and_product(const Array* arr) {
    Data sum = 0;     // Инициализируем переменную для суммы элементов массива
    Data product = 1; // Инициализируем переменную для произведения элементов массива
    for (size_t i = 0; i < array_size(arr); ++i) { // Проходим по всем элементам массива
        Data value = array_get(arr, i); // Получаем значение текущего элемента
        sum += value;      // Добавляем значение к общей сумме
        product *= value;  // Умножаем значение на общее произведение
    }
    cout << "Sum: " << sum << "\n";         // Выводим сумму элементов массива
    cout << "Product: " << product << "\n"; // Выводим произведение элементов массива
}

// Функция для вычисления суммы элементов между минимальным и максимальным
void process_array_min_max_sum(const Array* arr) {
    if (array_size(arr) < 2) { // Если размер массива меньше 2, операция невозможна
        cout << "Array too small.\n"; // Сообщаем об ошибке
        return; // Завершаем выполнение функции
    }

    size_t minIndex = 0, maxIndex = 0; // Индексы минимального и максимального элементов
    for (size_t i = 1; i < array_size(arr); ++i) { // Проходим по всем элементам массива
        if (array_get(arr, i) < array_get(arr, minIndex)) { // Проверяем, меньше ли текущий элемент минимального
            minIndex = i; // Обновляем индекс минимального элемента
        }
        if (array_get(arr, i) > array_get(arr, maxIndex)) { // Проверяем, больше ли текущий элемент максимального
            maxIndex = i; // Обновляем индекс максимального элемента
        }
    }

    if (minIndex > maxIndex) { // Если минимальный элемент расположен после максимального
        swap(minIndex, maxIndex); // Меняем их местами
    }

    Data sum = 0; // Инициализируем переменную для суммы
    for (size_t i = minIndex + 1; i < maxIndex; ++i) { // Проходим по элементам между minIndex и maxIndex
        sum += array_get(arr, i); // Добавляем значение элемента к сумме
    }

    cout << "Sum between min and max: " << sum << "\n"; // Выводим сумму между минимальным и максимальным элементами
}

// Главная функция программы
int main() {
    try { // Начинаем блок обработки исключений
        int size; // Переменная для хранения размера массива
        string filename1 = "input1.txt"; // Имя файла для первой задачи
        string filename2 = "input2.txt"; // Имя файла для второй задачи

        // Первая задача
        cout << "Enter size of array for first task: "; // Запрашиваем размер массива у пользователя
        cin >> size; // Считываем размер массива

        Array* arr1 = array_create(size); // Создаем массив заданного размера
        fill_array_from_file(arr1, filename1); // Заполняем массив данными из файла input1.txt
        cout << "First task:\n"; // Заголовок для вывода результатов первой задачи
        process_array_sum_and_product(arr1); // Вызываем функцию для обработки массива
        array_delete(arr1); // Удаляем массив и освобождаем память

        // Вторая задача
        cout << "\nEnter size of array for second task: "; // Запрашиваем размер массива для второй задачи
        cin >> size; // Считываем размер массива

        Array* arr2 = array_create(size); // Создаем массив заданного размера
        fill_array_from_file(arr2, filename2); // Заполняем массив данными из файла input2.txt
        cout << "Second task:\n"; // Заголовок для вывода результатов второй задачи
        process_array_min_max_sum(arr2); // Вызываем функцию для обработки массива
        array_delete(arr2); // Удаляем массив и освобождаем память

    }
    catch (const exception& e) { // Обрабатываем исключения, возникающие в программе
        cerr << "Error: " << e.what() << "\n"; // Выводим сообщение об ошибке
    }

    return 0; // Возвращаем 0, что означает успешное завершение программы
}




