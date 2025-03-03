#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <map>
#include <limits>

using namespace std;

class FixedSizeArray {
private:
    vector<int> data;
    size_t size;

public:
    FixedSizeArray(size_t size) : size(size), data(size) {}

    size_t getSize() const {
        return size;
    }

    int& operator[](size_t index) {
        return data[index];
    }

    const int& operator[](size_t index) const {
        return data[index];
    }
};


int findMaxEvenIndex(const FixedSizeArray& arr) {
    if (arr.getSize() == 0) {
        return numeric_limits<int>::min(); 
    }

    int maxVal = numeric_limits<int>::min();

    for (size_t i = 0; i < arr.getSize(); i += 2) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }

    return maxVal;
}

int findMostFrequent(const FixedSizeArray& arr) {
    if (arr.getSize() == 0) {
        return numeric_limits<int>::min();
    }

    map<int, int> counts;
    for (size_t i = 0; i < arr.getSize(); ++i) {
        counts[arr[i]]++;
    }

    int mostFrequent = arr[0];
    int maxCount = 0;

    for (const auto& pair : counts) {
        if (pair.second > maxCount) {
            mostFrequent = pair.first;
            maxCount = pair.second;
        }
    }

    return mostFrequent;
}


int main() {
    setlocale(LC_ALL, "Russian");
	
    size_t size1;
    cout << "Введите размер массива для задачи 1: ";
    cin >> size1;

    FixedSizeArray arr1(size1);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 100);

    cout << "Массив 1: ";
    for (size_t i = 0; i < size1; ++i) {
        arr1[i] = distrib(gen);
        cout << arr1[i] << " ";
    }
    cout << endl;

    int maxEven = findMaxEvenIndex(arr1);
    cout << "Максимальное значение среди элементов с четными индексами: " << maxEven << endl;

    // Task 2
    size_t size2;
    cout << "Введите размер массива для задания 2: ";
    cin >> size2;

    FixedSizeArray arr2(size2);
    cout << "Массив 2: ";
    for (size_t i = 0; i < size2; ++i) {
        arr2[i] = distrib(gen);
        cout << arr2[i] << " ";
    }
    cout << endl;

    int mostFrequent = findMostFrequent(arr2);
    cout << "Наиболее часто встречающийся элемент в массиве: " << mostFrequent << endl;

    return 0;
}
