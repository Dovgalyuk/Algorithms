#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

class Array {
private:
    int* data;
    size_t size;
public:
    Array(size_t size) : size(size) {
        data = new int[size];
    }
    ~Array() {
        delete[] data;
    }
    Array(const Array& other) : size(other.size) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i)
            data[i] = other.data[i];
    }
    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            for (size_t i = 0; i < size; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }
    int& operator[](size_t index) {
        if (index >= size) throw out_of_range("Индекс вне диапазона");
        return data[index];
    }
    const int& operator[](size_t index) const {
        if (index >= size) throw out_of_range("Индекс вне диапазона");
        return data[index];
    }
    size_t getSize() const {
        return size;
    }
};

void countElementsGreaterThanSum(const Array& arr) {
    int sum = 0;
    for (size_t i = 0; i < arr.getSize(); ++i) {
        sum += arr[i];
    }
    int count = 0;
    cout << "Индексы элементов, больших суммы всех элементов массива: ";
    for (size_t i = 0; i < arr.getSize(); ++i) {
        if (arr[i] > sum) {
            cout << i << " ";
            ++count;
        }
    }
    cout << endl;
    cout << "Количество таких элементов: " << count << endl;
}

void printUniqueElements(const Array& arr) {
    vector<int> elements;
    vector<int> counts;
    for (size_t i = 0; i < arr.getSize(); ++i) {
        int val = arr[i];
        bool found = false;
        for (size_t j = 0; j < elements.size(); ++j) {
            if (elements[j] == val) {
                counts[j]++;
                found = true;
                break;
            }
        }
        if (!found) {
            elements.push_back(val);
            counts.push_back(1);
        }
    }
    cout << "Элементы, которые встречаются только один раз: ";
    for (size_t i = 0; i < elements.size(); ++i) {
        if (counts[i] == 1) {
            cout << elements[i] << " ";
        }
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "ru");

    int n = 0;
    if (argc > 1) {
        n = atoi(argv[1]);
        if (n <= 0) {
            cerr << "Неверный размер массива" << endl;
            return 1;
        }
        cout << "Размер массива из аргумента командной строки: " << n << endl;
    }
    else {
        cout << "Введите размер массива: ";
        if (!(cin >> n) || n <= 0) {
            cerr << "Неверный размер массива" << endl;
            return 1;
        }
    }

    Array arr(n);
    ifstream infile("input.txt");
    if (!infile) {
        cerr << "Ошибка при открытии файла input.txt." << endl;
        return 1;
    }
    for (int i = 0; i < n; ++i) {
        if (!(infile >> arr[i])) {
            cerr << "Недостаточно данных в файле для заполнения массива." << endl;
            return 1;
        }
    }
    infile.close();

    countElementsGreaterThanSum(arr);
    printUniqueElements(arr);

    return 0;
}
