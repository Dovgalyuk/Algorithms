#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <locale.h>

// Функция для нахождения элемента, наиболее близкого к среднему значению
void find_closest_to_average(const std::vector<double>& arr) {
    if (arr.empty()) {
        std::cout << "The array is empty!" << std::endl;
        return;
    }

    // Вычисляем среднее значение
    double sum = 0.0;
    for (double val : arr) {
        sum += val;
    }
    double average = sum / arr.size();

    std::cout << "Average value: " << average << std::endl;

    // Находим элемент, наиболее близкий к среднему
    double closest = arr[0];
    double min_diff = std::abs(arr[0] - average);

    for (size_t i = 1; i < arr.size(); ++i) {
        double diff = std::abs(arr[i] - average);
        if (diff < min_diff) {
            min_diff = diff;
            closest = arr[i];
        }
    }

    std::cout << "Element closest to average: " << closest << std::endl;
    std::cout << "Difference: " << min_diff << std::endl;
}

// Функция для сжатия массива
void compress_array(std::vector<double>& arr, double a, double b) {
    std::cout << "Original array: ";
    for (double val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    size_t write_index = 0;

    // Перемещаем элементы, которые не в интервале [a, b]
    for (size_t read_index = 0; read_index < arr.size(); ++read_index) {
        if (arr[read_index] < a || arr[read_index] > b) {
            arr[write_index] = arr[read_index];
            write_index++;
        }
    }

    // Заполняем оставшиеся элементы нулями
    for (size_t i = write_index; i < arr.size(); ++i) {
        arr[i] = 0.0;
    }

    std::cout << "Compressed array: ";
    for (double val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    setlocale(LC_ALL, "Russian");
    setlocale(LC_ALL, "");
    setlocale(LC_ALL, "ru_RU.866");
    std::ifstream input_file("input.txt");

    if (!input_file.is_open()) {
        std::cerr << "Error: Failed to open input.txt file" << std::endl;
        return 1;
    }

    // Задача 1: Найти элемент, наиболее близкий к среднему
    std::cout << "=== Task 1: Find element closest to average ===" << std::endl;

    int size1;
    input_file >> size1;

    if (size1 <= 0) {
        std::cerr << "Error: invalid array size" << std::endl;
        return 1;
    }

    std::vector<double> arr1(size1);
    for (int i = 0; i < size1; ++i) {
        input_file >> arr1[i];
    }

    find_closest_to_average(arr1);

    std::cout << std::endl;

    // Задача 2: Сжать массив
    std::cout << "=== Task 2: Array compression ===" << std::endl;

    int size2;
    input_file >> size2;

    if (size2 <= 0) {
        std::cerr << "Error: invalid array size" << std::endl;
        return 1;
    }

    std::vector<double> arr2(size2);
    for (int i = 0; i < size2; ++i) {
        input_file >> arr2[i];
    }

    double a, b;
    input_file >> a >> b;

    std::cout << "Interval for removal: [" << a << ", " << b << "]" << std::endl;
    compress_array(arr2, a, b);

    input_file.close();

    return 0;
}