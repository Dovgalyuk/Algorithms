#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Реализация динамического массива с неизменяемым размером
class Array {
private:
    int* data;
    size_t size;
public:
    // Конструктор
    Array(size_t size) : size(size) {
        data = new int[size];
    }
    // Деструктор
    ~Array() {
        delete[] data;
    }
    // Копирующий конструктор
    Array(const Array& other) : size(other.size) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i)
            data[i] = other.data[i];
    }
    // Оператор присваивания
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
    // Оператор доступа
    int& operator[](size_t index) {
        if (index >= size) throw out_of_range("Индекс вне диапазона");
        return data[index];
    }
    // Константный оператор доступа
    const int& operator[](size_t index) const {
        if (index >= size) throw out_of_range("Индекс вне диапазона");
        return data[index];
    }
    // Получение размера
    size_t getSize() const {
        return size;
    }
};

// Функция для обработки массива (пункт 4)
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

// Функция для обработки массива (пункт 5)
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

int main() {
    setlocale(LC_ALL, "ru");
    int n;
    cout << "Введите размер массива: ";
    cin >> n;

    // Создаем массив и заполняем его из файла
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

    // Вызываем функции обработки массива
    countElementsGreaterThanSum(arr);
    printUniqueElements(arr);

    return 0;
}
