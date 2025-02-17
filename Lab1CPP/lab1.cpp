#include <iostream>
#include <ctime>
#include <fstream>
#include "array.h"

void array_fill(Array* arr) {
    for (size_t i = 0; i < array_size(arr); ++i) {
        array_set(arr,i, rand() % 20 + 1);
    }
}
void array_print(size_t size, size_t index, Data value) {
    std::cout << value;
    if(index != size-1){
        std::cout << (index % 2 == 0 ? " -" : " ");
    }
}
Data array_sum_elements(const Array* arr){
    Data sum = 0;
    std::cout << "Array: ";  
    size_t size = array_size(arr);
    for (size_t i = 0; i < size; ++i){
        Data value = array_get(arr, i);
        sum += (i % 2 == 0) ? value : -value;
        array_print(size, i, value);
    }
    return sum;
}   
Data find_max_sum_elements(const Array* arr) {
    size_t size = array_size(arr);
    if (size < 5) {
        std::cerr << "Ошибка: Массив слишком мал для поиска 5 элементов." << std::endl;
        return 1;
    }

    Data maxSum = 0;
    Data currentSum = 0;

    for (size_t i = 0; i < 5; ++i) {
        currentSum += (i % 2 == 0) ? array_get(arr, i) : -array_get(arr, i);
    }
    maxSum = currentSum;

    for (size_t i = 1; i <= size - 5; ++i) {
        Data oldValue = array_get(arr, i - 1); 
        Data newValue = array_get(arr, i + 4); 

        currentSum -= ((i - 1) % 2 == 0) ? oldValue : -oldValue;
        currentSum += ((i + 4) % 2 == 0) ? newValue : -newValue;

        if (currentSum > maxSum) {
            maxSum = currentSum;
        }
    }
    return maxSum;
}
int main(int argc, char* argv[]) {
    std::istream* input = &std::cin;
    std::ifstream inputFile;
    size_t arraySize;

    if (argc >= 1) {
        inputFile.open(argv[1]);
        if (!inputFile) {
            std::cerr << "Ошибка: файл не найден: " << argv[1] << std::endl;
            return 1;
        }
        input = &inputFile;
    }

    if (!(*input >> arraySize)) {
        std::cerr << "Ошибка: некорректный ввод данных. Введите размер массива." << std::endl;
        return 1;
    }

    if (arraySize == 0) {
        std::cerr << "Ошибка: Размер массива не может быть равен нулю." << std::endl;
        return 1;
    }

    Array* array = array_create(arraySize);
    array_fill(array);

    Data arraySumElements = array_sum_elements(array);
    std::cout << std::endl;
    std::cout << "Результат суммы элементов массива: " << arraySumElements << std::endl;

    Data findMaxSumElements  = find_max_sum_elements(array);
    
    std::cout << "Максимальная сумма элементов массива: " << findMaxSumElements << std::endl;

    system("pause");
    array_delete(array);

    return 0;
}