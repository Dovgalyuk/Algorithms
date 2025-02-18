#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include "array.h"

// Функция для чтения массива из файла
Array* array_create_and_read(std::ifstream& input) {
    int n;
    input >> n;

    if (input.fail() || n <= 0) {
        std::cerr << "Error: Invalid array size in input file." << std::endl;
        return nullptr;
    }

    Array* arr = array_create(n);

    if (arr == nullptr) {
        std::cerr << "Error: Failed to create array." << std::endl;
        return nullptr;
    }

    for (int i = 0; i < n; ++i) {
        int x;
        input >> x;

        if (input.fail()) {
            std::cerr << "Error: Invalid data in input file at index " << i << std::endl;
            array_delete(arr);
            return nullptr;
        }

        try {
            array_set(arr, i, x);
        }
        catch (const std::exception& e) {
            std::cerr << "Exception setting array element: " << e.what() << std::endl;
            array_delete(arr);
            return nullptr;
        }
    }
    return arr;
}

void task1(Array* arr) {
    if (arr == nullptr) {
        std::cerr << "Error: Array is NULL in task1" << std::endl;
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 100); // Случайные числа от 1 до 100

    // Заполние массива случайными числами и преобразование элементов
    std::cout << "Task 1: Array with transformed elements" << std::endl;
    for (size_t i = 0; i < array_size(arr); ++i) {
        Data randomNumber = distrib(gen);
        array_set(arr, i, randomNumber);

        try {
            Data element = array_get(arr, i);
            if (element % 2 == 0) {
                array_set(arr, i, element * element); // Четные элементы в квадрат
            }
            else {
                array_set(arr, i, element * 2);       // Нечетные элементы умножаем на 2
            }
            std::cout << "Element " << i << ": " << array_get(arr, i) << std::endl;

        }
        catch (const std::exception& e) {
            std::cerr << "Exception processing element " << i << ": " << e.what() << std::endl;
        }
    }
}

void task2(Array* arr) {
    if (arr == nullptr) {
        std::cerr << "Error: Array is NULL in task2" << std::endl;
        return;
    }

    int shiftSteps;
    char direction;

    std::cout << "Enter shift direction (l for left, r for right): ";
    std::cin >> direction;

    std::cout << "Enter number of shift steps: ";
    std::cin >> shiftSteps;

    if (std::cin.fail()) {
        std::cerr << "Error: Invalid input for shift steps." << std::endl;
        return;
    }

    size_t arraySize = array_size(arr); // Получаем размер массива один раз

    std::cout << "Task 2: Array after each shift step" << std::endl;
    for (int step = 0; step < shiftSteps; ++step) {
        if (direction == 'l') {
            // Сдвиг влево
            for (size_t i = 0; i < arraySize - 1; ++i) {
                try {
                    array_set(arr, i, array_get(arr, i + 1));
                }
                catch (const std::exception& e) {
                    std::cerr << "Error moving element left at index " << i << ": " << e.what() << std::endl;
                }
            }
            try {
                array_set(arr, arraySize - 1, 0);
            }
            catch (const std::exception& e) {
                std::cerr << "Error setting last element to 0: " << e.what() << std::endl;
            }
        }
        else if (direction == 'r') {
            // Сдвиг вправо
            for (size_t i = arraySize - 1; i > 0; --i) {
                try {
                    array_set(arr, i, array_get(arr, i - 1));
                }
                catch (const std::exception& e) {
                    std::cerr << "Error moving element right at index " << i << ": " << e.what() << std::endl;
                }
            }
            try {
                array_set(arr, 0, 0);
            }
            catch (const std::exception& e) {
                std::cerr << "Error setting first element to 0: " << e.what() << std::endl;
            }
        }
        else {
            std::cerr << "Error: Invalid direction. Use 'l' or 'r'." << std::endl;
            return;
        }
        // Вывод массива после каждого шага
        for (size_t i = 0; i < arraySize; ++i) {
            try {
                std::cout << array_get(arr, i) << " ";
            }
            catch (const std::exception& e) {
                std::cerr << "Error printing element at index " << i << ": " << e.what() << std::endl;
            }
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[]) {
    std::string filename = "input.txt";

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file: " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    Array* arr = array_create_and_read(inputFile); 
    if (arr != nullptr) {
        task1(arr);
        array_delete(arr);
        arr = nullptr; // Обнуляем, чтобы случайно не использовать освобожденную память
    }

    // Повторное открытие файла для чтения второго массива, если нужно

    // Ввод размера массива и сдвиг с клавиатуры
    size_t arraySize;
    std::cout << "Enter array size: ";
    std::cin >> arraySize;

    if (std::cin.fail() || arraySize <= 0) {
        std::cerr << "Error: Invalid array size." << std::endl;
        return EXIT_FAILURE;
    }

    Array* arr2 = array_create(arraySize);

    if (arr2 == nullptr) {
        std::cerr << "Error: Failed to create array." << std::endl;
        return EXIT_FAILURE;
    }

    task2(arr2);  

    array_delete(arr2);
    arr2 = nullptr;


    inputFile.close();

    return 0;
}
