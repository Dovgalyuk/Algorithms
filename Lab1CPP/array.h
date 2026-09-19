#ifndef ARRAY_H
#define ARRAY_H

// Реализовать контейнер - динамический массив array с неизменяемым размером (на любом из языков)
// Класс-контейнер "динамический массив с неизменяемым размером"
template <typename T>
class Array {
private:
    T* data;   // Указатель на начало массива
    int size;  // Размер массива

public:
    Array(int n) {  // При создании контейнера сразу выделяем память нужного размера (Конструктор)
        size = n;
        data = new T[n];
    }
    ~Array() { // При удалении контейнера память автоматически очищается (Десктуктор)
        delete[] data;
    }

    int getSize() {
        return size;
    }
    T& operator[](int index) {
        return data[index];
    }
};

#endif
