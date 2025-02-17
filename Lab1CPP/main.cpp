#include <iostream>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <cstdlib>

const double GROWTH_FACTOR = 1.5; // Коэффициент увеличения размера вектора при переполнении

// Класс, реализующий динамический массив с неизменяемым размером
class MyArray {
private:
    std::vector<int> data; // Вектор для хранения элементов массива
    int capacity; // Текущая емкость массива

    // Метод для увеличения размера массива при необходимости
    void expandIfNeeded() {
        if (data.size() >= capacity) {
            capacity = static_cast<int>(capacity * GROWTH_FACTOR);
            data.resize(capacity);
        }
    }

public:
    // Конструктор, заполняющий массив случайными числами
    MyArray(int size) : capacity(size) {
        data.resize(size);
        for (int &val : data) {
            val = rand() % 50; // Генерация случайных чисел от 0 до 49
        }
    }

    // Метод для вывода массива на экран
    void print() const {
        for (int val : data) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    // Метод для добавления элемента с учетом динамического увеличения
    void addElement(int value) {
        expandIfNeeded();
        data.push_back(value);
    }

    // Метод для подсчета суммы элементов, не превышающих заданное значение
    int sumElementsNotExceeding(int limit) const {
        int sum = 0;
        for (int val : data) {
            if (val <= limit) {
                sum += val;
            }
        }
        return sum;
    }

    // Метод для поиска наиболее часто встречающегося числа в массиве
    int mostFrequentElement() const {
        std::unordered_map<int, int> frequency;
        for (int val : data) {
            frequency[val]++;
        }

        int maxCount = 0, mostFrequent = data[0];
        for (const auto &pair : frequency) {
            if (pair.second > maxCount) {
                maxCount = pair.second;
                mostFrequent = pair.first;
            }
        }
        return mostFrequent;
    }
};

int main() {
    srand(time(0)); // Инициализация генератора случайных чисел

    int size1;
    std::cout << "Введите размер массива для подсчета суммы: ";
    std::cin >> size1;
    MyArray arr1(size1); // Создание первого массива
    arr1.print();
    std::cout << "Сумма элементов (<=20): " << arr1.sumElementsNotExceeding(20) << std::endl;

    int size2;
    std::cout << "Введите размер массива для поиска самого частого элемента: ";
    std::cin >> size2;
    MyArray arr2(size2); // Создание второго массива
    arr2.print();
    std::cout << "Наиболее часто встречающееся число: " << arr2.mostFrequentElement() << std::endl;

    return 0;
}
