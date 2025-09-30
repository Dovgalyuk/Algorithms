#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <stdexcept>
#include <locale>
#include <windows.h>

using namespace std;

void setRussianLocale() { // функция русской локализации (кроссплатформенная)
    try {
        locale::global(locale("ru_RU.UTF-8"));
    } catch (const exception&) {
        try {
            locale::global(locale("Russian_Russia.1251"));
        } catch (const exception&) {
            cout << "Не удалось установить русскую локаль, используется локаль по умолчанию" << endl;
        }
    }
}

class FixedArray {
private:
    vector<int> data; // вектор хранения данных массива
    size_t capacity; // размер массива

public:
    FixedArray(size_t size) : capacity(size) { // создание массива заданного размера
        data.resize(size); // изменение размера до требуемого
    }

    size_t size() const { // метод получения размера массива
        return capacity;
    }

    void fillFromFile(const string& filename) { // метод заполнения массива данными из файла
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Невозможно открыть файл:" + filename);
        }
        
        for (size_t i = 0; i < capacity; ++i) {
            if (!(file >> data[i])) {
                throw runtime_error("Недостаточно номеров в файле");
            }
        }
    }

    void print() const { // метод вывода массива на экран
        cout << "Массив (" << capacity << " элементов): ";
        for (size_t i = 0; i < capacity; ++i) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    int countAbsoluteGreaterThanMax() const { // метод подсчета абсолютного максимального числа 
        if (data.empty()) return 0;
        
        int max_value = data[0];
        for (size_t i = 1; i < capacity; ++i) {
            if (data[i] > max_value) {
                max_value = data[i];
            }
        }
        
        int count = 0;
        int abs_max = abs(max_value);
        
        for (size_t i = 0; i < capacity; ++i) {
            if (abs(data[i]) > abs_max) {
                count++;
            }
        }
        
        return count;
    }

    vector<int> findMaxSumFiveConsecutive() const { // метод для поиска 5 последовательных элементов с максимальной суммой
        if (capacity < 5) {
            throw runtime_error("Размер массива должен быть не менее 5");
        }

        int max_sum = INT_MIN; // начальное значение максимальной суммы
        size_t start_index = 0; // индекс начала последовательности

        for (size_t i = 0; i <= capacity - 5; ++i) { // перебор всех возможных последовательностей
            int current_sum = 0;
            for (size_t j = 0; j < 5; ++j) {
                current_sum += data[i + j];
            }
            
            if (current_sum > max_sum) { // подсчет суммы из 5 элементов
                max_sum = current_sum;
                start_index = i;
            }
        }

        return vector<int>(data.begin() + start_index, // возврат найденной последовательности 5 элементов
                          data.begin() + start_index + 5);
    }
};

void task4() {
    cout << "Задание 4: Подсчет элементов, чье абсолютное значение больше максимального." << endl;
    
    ifstream size_file("input_size.txt"); // просмотр размера массива
    if (!size_file.is_open()) {
        throw runtime_error("Невозможно открыть input_size.txt");
    }
    
    int size;
    size_file >> size;
    cout << "Размер массива: " << size << endl;
    
    FixedArray arr(size); // создается и заполняется массив
    arr.fillFromFile("input_data.txt");
    arr.print();
    
    int result = arr.countAbsoluteGreaterThanMax(); // выполнение подсчета и вывод на экран
    cout << "Результат: " << result << " элементы имеют абсолютное значение больше максимального" << endl;
}

void task5() {
    cout << "\nЗадание 5: Нахождение пяти последовательных элементов с максимальной суммой." << endl;
    
    ifstream size_file("input_size2.txt"); // просмотр размера массива
    if (!size_file.is_open()) {
        throw runtime_error("Невозможно открыть input_size2.txt");
    }
    
    int size;
    size_file >> size;
    cout << "Размер массива: " << size << endl;
    
    FixedArray arr(size); // создание и заполнение
    arr.fillFromFile("input_data2.txt");
    arr.print();
    
    auto result = arr.findMaxSumFiveConsecutive(); // нахождение последовательности и вывод результата
    
    cout << "Пять последовательных элементов с максимальной суммой: ";
    int sum = 0;
    for (int num : result) {
        cout << num << " ";
        sum += num;
    }
    cout << "(Сумма = " << sum << ")" << endl;
}

int main() {
    setRussianLocale(); // установка локали
    
    try {
        cout << "Программа обработки фиксированных массивов" << endl;
        cout << "---------------------------------------------------" << endl;
        
        task4();
        task5();
        
    } catch (const exception& e) { // обработка ошибок 
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}