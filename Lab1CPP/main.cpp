#include <iostream>
#include <cstdlib>  
#include <ctime>    
#include "array.h"
#include <fstream>

using namespace std;

bool is_prime(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) return false;
    }
    return true;
}

void fill_with_primes(Array* arr) {
    int num = 2, count = 0;
    while (count < static_cast<int>(array_size(arr))) {  
        if (is_prime(num)) {
            array_set(arr, count, num);
            count++;
        }
        num++;
    }
}

void fill_with_random(Array* arr) {
    srand(static_cast<unsigned int>(time(nullptr)));  
    for (size_t i = 0; i < array_size(arr); ++i) {
        array_set(arr, i, rand() % 100); 
    }
}

void find_max_sum_segment(Array* arr) {
    if (array_size(arr) < 5) {
        cout << "Массив слишком мал для поиска 5 элементов." << endl;
        return;
    }

    int max_sum = 0, max_index = 0;

    // Считаем сумму первых 5 элементов
    for (size_t i = 0; i < 5; ++i) {
        max_sum += array_get(arr, i);
    }

    int current_sum = max_sum;
  
    for (size_t i = 1; i <= array_size(arr) - 5; ++i) {
        current_sum = current_sum - array_get(arr, i - 1) + array_get(arr, i + 4);

        if (current_sum > max_sum) {
            max_sum = current_sum;
            max_index = static_cast<int>(i);  
        }
    }

    // Выводим результат
    cout << "Максимальная сумма: " << max_sum << " (элементы с индекса " << max_index << " по " << max_index + 4 << ")" << endl;
    cout << "Элементы: ";
    for (size_t i = max_index; i < max_index + 5; ++i) {
        cout << array_get(arr, i) << " ";
    }
    cout << endl;
}

// Главная функция
int main(int argc, char* argv[]) {
    istream* input = &cin;
    ifstream inputFile;
    size_t N, M;

    if (argc >= 2) {
        inputFile.open(argv[1]);
        if (!inputFile) {
            cerr << "Ошибка: не удалось открыть файл " << argv[1] << endl;
            return 1;
        }
        input = &inputFile;
    }

    if (!(*input >> N >> M)) {
        cerr << "Ошибка: некорректный ввод данных" << endl;
        return 1;
    }

    Array* prime_array = array_create(N);
    fill_with_primes(prime_array);

    cout << "Массив простых чисел: ";
    for (size_t i = 0; i < array_size(prime_array); ++i) {
        cout << array_get(prime_array, i) << " ";
    }
    cout << endl;
    array_delete(prime_array);

    Array* random_array = array_create(M);
    fill_with_random(random_array);

    cout << "Массив случайных чисел: ";
    for (size_t i = 0; i < array_size(random_array); ++i) {
        cout << array_get(random_array, i) << " ";
    }
    cout << endl;

    find_max_sum_segment(random_array);
    array_delete(random_array);

    return 0;
}