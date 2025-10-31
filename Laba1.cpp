#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>

using namespace std;

// Чтение файла
vector<int> read_vector_from_file(ifstream& input) {
    int n;
    vector<int> arr(n);

    for (int i = 0; i < n; ++i) {
        int x;
        arr[i] = x;
    }

    return arr;
}

// Функция расчёта осадков в половинах
void compare_halves(const vector<int>& arr) {

    if (arr.size() != 30) {
        cout << "Ошибка: в июне всегда 30 дней!\n";
        return;
    }

    // Объявление суммы половин месяца
    long long half1_sum = 0; 
    long long half2_sum = 0;

    for (int i = 0; i < 15; ++i) {              // Сумма первой половины месяца
        half1_sum = half1_sum + arr[i];
    }

    for (int i = 15; i < 30; ++i) {              // Сумма второй половины месяца
        half2_sum = half2_sum + arr[i];
    }

    // Вывод сумм
    cout << "Сумма осадков первой половины июня: " << half1_sum << endl;
    cout << "Сумма осадков второй половины июня: " << half2_sum << endl;

    if (half1_sum > half2_sum) {
        cout << "Осадков больше в первой половине месяца\n";
    }
    else if (half2_sum > half1_sum) {
        cout << "Осадков больше во второй половине месяца\n";
    }
    else {
        cout << "Осадков выпало одинаково в двух половинах\n";
    }
}

// Функция на определение самой влажной декады
void find_wettest_decade(const vector<int>& arr) {

    if (arr.size() != 30) {
        cout << "Ошибка: в июне 30 дней";
        return;
    }

    long long decade1_sum = 0;
    long long decade2_sum = 0;
    long long decade3_sum = 0;

    for (int i = 0; i < 10; ++i) { // Первая декада
        decade1_sum = decade1_sum + arr[i];
    }

    for (int i = 10; i < 20; ++i) { // Вторая декада
        decade2_sum = decade2_sum + arr[i];
    }

    for (int i = 20; i < 30; ++i) { // Третья декада
        decade3_sum = decade3_sum + arr[i];
    }

    // Нахождение наибольшей декады

    long long max_sum = decade1_sum;
    int max_decade = 1;

    if (decade2_sum > max_sum) {
        max_sum = decade2_sum;
        max_decade = 2;
    }

    if (decade3_sum > max_sum) {
        max_sum = decade3_sum;
        max_decade = 3;
    }

    cout << "Декада 1(1-10): " << decade1_sum << endl;
    cout << "Декада 2(11-20): " << decade2_sum << endl;
    cout << "Декада 3(21-30): " << decade3_sum << endl;
    cout << "Наибольшее количество осадков выпало в " << max_decade << "декаде, а конкретно: " << max_sum << endl;
}

// Функция по нахождению наиболее встречающегося числа 

void most_common_number(const vector<int>& arr) {

    // Set нужен для считывания уникальных чисел
    set<int> unique_elements(arr.begin(), arr.end());

    int max_freq = 0;
    int most_frequent_num = arr[0];

    // Цикл считывает ункикальные элементы
    for (int current_val : unique_elements) {
        int current_freq = 0;

        // Внутренний цикл считывает количество уникальных элементов
        for (int array_val : arr) {
            if (array_val == current_val) {
                current_freq = current_freq + 1;
            }
        }

        // Обновление максимума
        if (current_freq > max_freq) {
            max_freq = current_freq;
            most_frequent_num = current_val;
        }
    }
    
    cout << "Наиболее распространённое число: " << most_frequent_num << ", в количестве: " << max_freq << endl;
}

int main(int argc, char** argv) {

    if (argc < 2) {
        return 1;
    }

    ifstream input(argv[1]);

    vector<int> arr = read_vector_from_file(input);

    input.close();

    compare_halves(arr);
    find_wettest_decade(arr);
    most_common_number(arr);
}