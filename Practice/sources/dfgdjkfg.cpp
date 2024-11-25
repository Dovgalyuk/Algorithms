#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

class Array {
public:
    // Конструктор класса, который инициализирует массив фиксированного размера
    Array(size_t size) : size(size), data(size) {}

    // Функция для чтения данных из файла
    void fillFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Open file error!" << endl;
            return;
        }
        for (size_t i = 0; i < size; ++i) {
            file >> data[i];
        }
    }

    // Функция для подсчета суммы и произведения элементов массива
    void sumAndProduct() const {
        int sum = 0;
        long long product = 1;

        for (const int& num : data) {
            sum += num;
            product *= num;
        }

        cout << "Array: ";
        for (const int& num : data) {
            cout << num << " ";
        }
        cout << endl;

        cout << "Sum el: " << sum << endl;
        cout << "Proiz el: " << product << endl;
    }

    // Функция для вычисления суммы элементов между минимальным и максимальным
    // исключая сами минимальный и максимальный элементы
    void sumBetweenMinMax() const {
        if (data.size() < 3) {
            cout << "Slishkom maloe coll elem dly vipolneniy operatii" << endl;
            return;
        }

        int min_val = numeric_limits<int>::max();
        int max_val = numeric_limits<int>::min();
        size_t min_idx = 0, max_idx = 0;

        // Поиск минимального и максимального элементов
        for (size_t i = 0; i < size; ++i) {
            if (data[i] < min_val) {
                min_val = data[i];
                min_idx = i;
            }
            if (data[i] > max_val) {
                max_val = data[i];
                max_idx = i;
            }
        }

        int sum_between = 0;

        // Суммируем элементы, находящиеся между min и max
        size_t start = min(min_idx, max_idx) + 1;
        size_t end = max(min_idx, max_idx);

        for (size_t i = start; i < end; ++i) {
            sum_between += data[i];
        }

        cout << "Summ min i max znach(ne vkluchay ih): " << sum_between << endl;
    }

private:
    size_t size;
    vector<int> data;
};

int main() {
    // Ввод размера массива
    int n;
    cout << "Vvedite razmer massiva: ";
    cin >> n;

    // Создаем объект массива
    Array arr(n);

    // Вводим имя файла, из которого будет производиться чтение данных
    string filename;
    cout << "Vvedite imy file dly zagruzki dannih: ";
    cin >> filename;

    // Заполняем массив данными из файла
    arr.fillFromFile(filename);

    // Вычисляем сумму и произведение элементов массива
    arr.sumAndProduct();

    // Вычисляем сумму между минимальным и максимальным элементами
    arr.sumBetweenMinMax();

    return 0;
}

