#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stdexcept>

using namespace std;

vector<int> read_array(ifstream& input) {
    int n;
    input >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        input >> arr[i];
    }
    return arr;
}

// Найти количество элементов, значение которых больше среднего арифметического минимального и максимального элементов массива
void task1(const vector<int>& arr) {
    if (arr.empty()) return;

    int min = *min_element(arr.begin(), arr.end());
    int max = *max_element(arr.begin(), arr.end());
    double avg = (min + max) / 2.0;

    vector<size_t> indices;
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] > avg) {
            indices.push_back(i);
        }
    }

    cout << "Количество элементов, больших среднего арифметического min и max: " << indices.size() << endl;
    cout << "Индексы: ";
    for (size_t i : indices) {
        cout << i << " ";
    }
    cout << endl;
}

void task2(const vector<int>& arr) {
    if (arr.empty()) return;

    unordered_map<int, int> frequencyMap;
    for (int num : arr) {
        frequencyMap[num]++;
    }

    int mostFrequent = arr[0];
    int maxCount = 1;
    for (const auto& pair : frequencyMap) {
        if (pair.second > maxCount) {
            mostFrequent = pair.first;
            maxCount = pair.second;
        }
    }

    cout << "Самое частое число: " << mostFrequent << " (встречается " << maxCount << " раз)" << endl;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Использование: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input) {
        cerr << "Не удалось открыть файл." << endl;
        return 1;
    }

    vector<int> arr1 = read_array(input);
    task1(arr1);

    vector<int> arr2 = read_array(input);
    task2(arr2);

    input.close();
    return 0;
}