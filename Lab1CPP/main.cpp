#include <iostream>
#include <stdexcept>  

using namespace std;

template <typename T>
class Array {
private:
    T* data;
    size_t size;

public:
    // получаем размер массива
    Array(size_t size) : size(size) {
        if (size == 0) {
            data = nullptr; // 0 - не допустимый размер
        } else {
            data = new T[size];
        }
    }

    // копия
    Array(const Array& other) : size(other.size) {
        data = new T[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            // очищам память
            delete[] data;

            // Выделяем субсидии
            size = other.size;
            data = new T[size];

            // копир
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // передвижиния
    Array(Array&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }

    // присваивания движением
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;

            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }

    // деструктор
    ~Array() {
        delete[] data;
    }

    // доступ по индексу
    T& operator[](size_t index) {
        if (index >= size) {
            throw out_of_range("Индекс выходит за границы массива");
        }
        return data[index];
    }

    // константный оператор доступа по индексу
    const T& operator[](size_t index) const {
        if (index >= size) {
            throw out_of_range("Индекс выходит за границы массива");
        }
        return data[index];
    }

    // получение размера массива
    size_t getSize() const {
        return size;
    }

    // установка значения элемента
    void set(size_t index, const T& value) {
        if (index >= size) {
            throw out_of_range("Индекс выходит за границы массива");
        }
        data[index] = value;
    }

    // получение значения элемента
    T get(size_t index) const {
        if (index >= size) {
            throw out_of_range("Индекс выходит за границы массива");
        }
        return data[index];
    }
};

int main() {
	setlocale(LC_ALL, "Russian");
    try {
        Array<int> myArray(5);

        for (size_t i = 0; i < myArray.getSize(); ++i) {
            myArray[i] = i * 2;
        }

        for (size_t i = 0; i < myArray.getSize(); ++i) {
            cout << "Элемент " << i << ": " << myArray[i] << endl;
        }

        Array<int> myArray2 = myArray;
        Array<int> myArray3(10);
        myArray3 = myArray;
        Array<int> myArray4 = move(myArray3);
        myArray3 = move(myArray);


    } catch (const out_of_range& e) {
        cerr << "Ошибка: " << e.what() << endl;
    } catch (const std::exception& e) {
      cerr << "Ошибка: " << e.what() << endl;
    }

    return 0;
}
