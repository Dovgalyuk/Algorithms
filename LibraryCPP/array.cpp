#include <stdexcept>

using Data = int;

//Контейнер, хранящий указатель на данные типа Data и размер массива в виде переменной типа size_t.
struct Array {
    Data* data = nullptr;
    size_t size = 0;
};

// Создаёт массив указанного размера
Array* array_create(size_t size) {
    if (size == 0) {
        throw std::invalid_argument("Размер массива не может быть равен нулю.");
    }

    Array* arr = new Array;
    arr->data = new Data[size];
    arr->size = size;
    return arr;
}

// Удаляет массив и освобождает память
void array_delete(Array* arr) {
    if (arr) {
        delete[] arr->data;
        delete arr;
    }
}

// Возвращает элемент массива по индексу
Data array_get(const Array* arr, size_t index) {
    if (index >= arr->size) {
        throw std::out_of_range("Индекс выходит за пределы массива.");
    }
    return arr->data[index];
}

// Устанавливает значение элемента массива по индексу
void array_set(Array* arr, size_t index, Data value) {
    if (index >= arr->size) {
        throw std::out_of_range("Индекс выходит за пределы массива.");
    }
    arr->data[index] = value;
}

// Возвращает размер массива
size_t array_size(const Array* arr) {
    return arr->size;
}