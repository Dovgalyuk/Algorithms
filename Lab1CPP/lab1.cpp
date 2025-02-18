#include <iostream>
#include <ctime>
#include <fstream>
#include "array.h"

void array_fill(Array* arr) {
    for (size_t i = 0; i < array_size(arr); ++i)  {
        array_set(arr,i, rand() % 20 + 1);
    }
}
void array_print(const size_t size, const  size_t index, const Data value) {
    std::cout << value;
    if(index != size-1){
        std::cout << (index % 2 == 0 ? " -" : " ");
    }
}
Data array_alternating_sum(const Array* arr) {
    Data sum = 0;
    std::cout << "Array: ";  
    const size_t size = array_size(arr);
    for (size_t i = 0; i < size; ++i){
        Data value = array_get(arr, i);
        sum += (i % 2 == 0) ? value : -value;
        array_print(size, i, value);
    }
    return sum;
}   
Data find_max_sum(const Array* arr) {
    const size_t size = array_size(arr);
    if (size < 5) {
        std::cerr << "Ошибка: Массив слишком мал для поиска 5 элементов." << std::endl;
        return 1;
    }

    Data maxSum = 0;
    Data currentSum = 0;

    for (size_t i = 0; i < 5; ++i) {
        currentSum += array_get(arr, i);
    }
    maxSum = currentSum;
    for (size_t i = 5; i < size; ++i) {
        currentSum += array_get(arr, i) - array_get(arr, i - 5);
        maxSum = std::max(maxSum, currentSum);
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
        std::cerr << "Ошибка: Некорректный ввод данных. Введите размер массива." << std::endl;
        return 1;
    }

    if (arraySize == 0) {
        std::cerr << "Ошибка: Размер массива не может быть равен нулю." << std::endl;
        return 1;
    }

    Array* array = array_create(arraySize);
    array_fill(array);

    Data alternatingSum = array_alternating_sum(array);
    std::cout << std::endl;
    std::cout << "Результат суммы элементов массива: " << alternatingSum << std::endl;

    Data findMaxSum = find_max_sum(array);
    
    std::cout << "Максимальная сумма элементов массива: " << findMaxSum << std::endl;
    array_delete(array);

    return 0;
}