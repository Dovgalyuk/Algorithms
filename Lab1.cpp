#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void processRainfall(const vector<int>& rainfall) {
    int firstHalfSum = 0;
    int secondHalfSum = 0;

    // Вычисляем сумму осадков в первой половине и второй половине июня
    for (int i = 0; i < rainfall.size(); i++) {
        if (i < rainfall.size() / 2) {
            firstHalfSum += rainfall[i];
        }
        else {
            secondHalfSum += rainfall[i];
        }
    }

    // Определяем, в какой период выпало больше осадков
    if (firstHalfSum > secondHalfSum) {
        cout << "Больше осадков выпало в первую половину июня." << endl;
    }
    else if (secondHalfSum > firstHalfSum) {
        cout << "Больше осадков выпало во вторую половину июня." << endl;
    }
    else {
        cout << "Осадки равномерно распределены между первой и второй половиной июня." << endl;
    }

    // Находим декаду с наибольшим количеством осадков
    int maxDecade = -1;
    int maxDecadeRainfall = -1;
    for (int i = 0; i < rainfall.size(); i += 10) {
        int sum = 0;
        for (int j = i; j < i + 10 && j < rainfall.size(); j++) {
            sum += rainfall[j];
        }
        if (sum > maxDecadeRainfall) {
            maxDecadeRainfall = sum;
            maxDecade = i / 10 + 1;
        }
    }

    // Выводим декаду с наибольшим количеством осадков
    cout << "Наибольшее количество осадков выпало в " << maxDecade << "-ую декаду июня." << endl;
}

void findDuplicates(const vector<int>& array) {
    vector<int> duplicates;

    // Проверяем каждый элемент массива на наличие дубликатов
    for (int i = 0; i < array.size(); i++) {
        // Проверяем, сколько раз элемент встречается в массиве
        int count = std::count(array.begin(), array.end(), array[i]);
        if (count == 2) {
            duplicates.push_back(array[i]);
        }
    }

    // Выводим элементы, которые встречаются два раза
    cout << "Элементы, которые встречаются ровно два раза: ";
    for (int i = 0; i < duplicates.size(); i++) {
        cout << duplicates[i] << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int size;
    cout << "Введите размер массива: ";
    cin >> size;

    vector<int> rainfall(size);
    // Заполняем массив случайными числами
    for (int i = 0; i < size; i++) {
        rainfall[i] = rand() % 100; // Генерируем случайное число от 0 до 99
    }

    processRainfall(rainfall);

    findDuplicates(rainfall);

    return 0;
}
