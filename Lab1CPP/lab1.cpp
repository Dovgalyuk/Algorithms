#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include "array.h"

// Функция для вычисления факториала
int factorial(int n) {
    if (n <= 1) return 1;
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// Задание 1: Создать массив и заполнить значениями факториала от индекса элемента
void task1(std::ifstream &input) {
    int size;
    input >> size;
    
    Array *arr = array_create(size);
    
    // Заполняем массив значениями факториала от индекса
    for (int i = 0; i < size; ++i) {
        array_set(arr, i, factorial(i));
    }
    
    // Выводим массив на экран
    for (size_t i = 0; i < array_size(arr); ++i) {
        std::cout << array_get(arr, i);
        if (i < array_size(arr) - 1) std::cout << " ";
    }
    std::cout << std::endl;
    
    array_delete(arr);
}

// Задание 2: Найти элементы, которые встречаются ровно два раза
void task2(std::ifstream &input) {
    int size;
    input >> size;
    
    Array *arr = array_create(size);
    
    // Читаем значения из файла
    for (int i = 0; i < size; ++i) {
        int value;
        input >> value;
        array_set(arr, i, value);
    }
    
    // Подсчитываем частоту каждого элемента
    std::unordered_map<int, int> frequency;
    for (size_t i = 0; i < array_size(arr); ++i) {
        int value = array_get(arr, i);
        frequency[value]++;
    }
    
    // Находим элементы, которые встречаются ровно два раза
    bool first = true;
    for (size_t i = 0; i < array_size(arr); ++i) {
        int value = array_get(arr, i);
        if (frequency[value] == 2) {
            if (!first) std::cout << " ";
            std::cout << value;
            first = false;
            frequency[value] = 0; // Помечаем как уже выведенный
        }
    }
    if (!first) std::cout << std::endl;
    
    array_delete(arr);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }
    
    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Error: Cannot open file " << argv[1] << std::endl;
        return 1;
    }
    
    // Читаем номер задания из первой строки файла
    int task_number;
    input >> task_number;
    
    if (task_number == 1) {
        task1(input);
    } else if (task_number == 2) {
        task2(input);
    } else {
        std::cerr << "Error: Invalid task number. Use 1 or 2." << std::endl;
        input.close();
        return 1;
    }
    
    input.close();
    return 0;
}