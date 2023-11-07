#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

// Объявляем шаблонный класс Array для работы с массивами произвольного типа Data
template <typename Data>
class Array {
public:
    // Конструктор для создания массива
    explicit Array(size_t size) {
        this->data = new Data[size]; // Выделение памяти под массив
        this->size_array = size;     // Запоминание размера массива
    }

    // Деструктор для уничтожения массива и освобождения памяти
    ~Array() {
        delete[] data; // Освобождение памяти
    }

    // Конструктор копирования
    Array(const Array<Data>& a) {
        size_array = a.size_array;         // Копирование размера массива
        data = new Data[size_array];       // Выделение памяти под копию массива
        for (size_t i = 0; i < size_array; i++) {
            data[i] = a.data[i];           // Копирование элементов массива
        }
    }

    // Оператор присваивания
    Array& operator=(const Array<Data>& a) {
        if (this == &a) {
            // Проверка на самоприсваивание
            return *this;
        }

        // Удаление текущих данных
        delete[] data;

        // Глубокое копирование
        size_array = a.size_array;        // Копирование размера массива
        data = new Data[size_array];      // Выделение памяти под новый массив
        for (size_t i = 0; i < size_array; i++) {
            data[i] = a.data[i];          // Копирование элементов массива
        }

        return *this; // Возвращение текущего объекта
    }

    // Возвращает указатель на элемент массива по индексу
    Data* get(size_t index) const {
        return &data[index];
    }

    // Устанавливает значение элемента массива по индексу
    void set(size_t index, Data value) {
        data[index] = value;
    }

    // Возвращает размер массива
    size_t size() const { return this->size_array; }

    size_t size_array; // Переменная для хранения размера массива
private:
    Data* data; // Указатель на массив
};

#endif // ARRAY_TEMPLATE_H