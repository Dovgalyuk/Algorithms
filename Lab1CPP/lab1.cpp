#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "array.h"

using namespace std;

Array* array_create_and_read(ifstream &input) {
    int n;
    input >> n;  

    Array *arr = array_create(n); 
    if (arr == nullptr) {
        cout << "Ошибка при создании массива.\n";
        return nullptr;
    }

    for (int i = 0; i < n; ++i) {
        int x;
        input >> x;  
        array_set(arr, i, x);  // Заполнение массива
    }

    return arr;  
}

// Функция для задачи 1
void task1(Array *arr) {
    size_t half_size = array_size(arr) / 2;  
    int sum_first_half = 0, sum_second_half = 0;

    // Подсчет суммы осадков для первой и второй половины
    for (size_t i = 0; i < half_size; ++i) {
        sum_first_half += array_get(arr, i); 
        sum_second_half += array_get(arr, i + half_size); 
    }

    cout << "Задача 1: Сравнение осадков:\n";
    if (sum_first_half > sum_second_half) {
        cout << "Больше осадков в первой половине.\n";
    } else if (sum_second_half > sum_first_half) {
        cout << "Больше осадков во второй половине.\n";
    } else {
        cout << "Осадки равны в обеих половинах.\n";
    }

    // Определение декады с наибольшим количеством осадков
    int sum_first_decade = 0, sum_second_decade = 0, sum_third_decade = 0;
    size_t one_third = array_size(arr) / 3;
    for (size_t i = 0; i < one_third; ++i) {
        sum_first_decade += array_get(arr, i); 
        sum_second_decade += array_get(arr, i + one_third); 
        sum_third_decade += array_get(arr, i + 2 * one_third); 
    }

    cout << "Задача 1: Декада с наибольшими осадками:\n";
    if (sum_first_decade > sum_second_decade && sum_first_decade > sum_third_decade) {
        cout << "Первая декада имела больше всего осадков.\n";
    } else if (sum_second_decade > sum_first_decade && sum_second_decade > sum_third_decade) {
        cout << "Вторая декада имела больше всего осадков.\n";
    } else {
        cout << "Третья декада имела больше всего осадков.\n";
    }
}

// Функция для задачи 2
void task2(Array *arr, int kolvo_sdviga) {
    int direction;
    cout << "Введите направление сдвига (1 - влево, 2 - вправо): ";
    cin >> direction;

    size_t size = array_size(arr);  

    if (direction == 1) {  // Сдвиг влево
        for (int step = 0; step < kolvo_sdviga; ++step) {  
            for (size_t i = 0; i < size - 1; ++i) {
                array_set(arr, i, array_get(arr, i + 1));  
            }
            array_set(arr, size - 1, 0);  
            cout << "Массив после сдвига влево, шаг " << step + 1 << ":\n";
            for (size_t i = 0; i < size; ++i) {
                cout << array_get(arr, i) << " ";  
            }
            cout << '\n';
        }
    } else if (direction == 2) {  // Сдвиг вправо
        for (int step = 0; step < kolvo_sdviga; ++step) {  
            int last = array_get(arr, size - 1);  
            for (size_t i = size - 1; i > 0; --i) {
                array_set(arr, i, array_get(arr, i - 1));  
            }
            array_set(arr, 0, last);  
            cout << "Массив после сдвига вправо, шаг " << step + 1 << ":\n";
            for (size_t i = 0; i < size; ++i) {
                cout << array_get(arr, i) << " ";  
            }
            cout << '\n';
        }
    }
}

// Основная функция
int main(int argc, char **argv){
    if (argc < 2) {
        cout << "Не указан файл ввода.\n";
        return 1; 
    }

    ifstream input(argv[1]);
    if (!input.is_open()) {
        cout << "Не удалось открыть файл: " << argv[1] << '\n';
        return 1; 
    }

    // Выполняем задачу 1
    Array *arr = array_create_and_read(input); 
    if (arr) {
        task1(arr);  
        array_delete(arr);  
    }

    // Выполняем задачу 2
    arr = array_create_and_read(input); 
    if (arr) {
        int kolvo_sdviga;
        input >> kolvo_sdviga;  // Считываем количество шагов из файла
        task2(arr, kolvo_sdviga);  
        array_delete(arr);  
    }

    input.close();  
    return 0;  
}
