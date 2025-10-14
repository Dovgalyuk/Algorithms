#include "vector.h"

Vector::Vector()
{
    adata = nullptr;
    asize = 0;
    acapacity = 0;
}

Vector::Vector(const Vector& a)
{
    if (a.size() > 0) {
        asize = a.size();
        acapacity = a.acapacity;
        Data* new_data = new Data[acapacity];
        for (size_t i = 0; i < asize; i++) {
            new_data[i] = a.get(i);
        }
        adata = new_data;
    }
    else {
        adata = nullptr;
        asize = 0;
        acapacity = 0;
    }
}

Vector& Vector::operator=(const Vector& a)
{
    if (this != &a) {
        if (a.size() > 0) {
            delete[] adata;
            asize = a.size();
            acapacity = a.acapacity;
            Data* new_data = new Data[acapacity];
            for (size_t i = 0; i < asize; i++) {
                new_data[i] = a.get(i);
            }
            adata = new_data;
        }
        else {
            adata = nullptr;
            asize = 0;
            acapacity = 0;
        }
    }
    return *this;
}

Vector::~Vector()
{
    delete[] adata;
}

Data Vector::get(size_t index) const
{
    if (index < asize) {
        return adata[index];
    }
    else {
        return -1;
    }
}

void Vector::set(size_t index, Data value)
{
    if (index < asize) {
        adata[index] = value;
    }
}

size_t Vector::size() const
{
    return asize;
}

void Vector::resize(size_t size)
{
    if (size <= acapacity) {
        // Если новый размер меньше или равен текущей вместимости,
        // просто меняем размер без перевыделения памяти
        asize = size;
    }
    else {


        // Вычисляем новую вместимость с запасом для достижения O(1) в среднем
        size_t new_capacity = size * 2; // стандартный коэффициент роста

        // Создаем новый массив с новой вместимостью
        Data* new_data = new Data[new_capacity];

        // Копируем существующие данные
        for (size_t i = 0; i < asize; ++i) {
            new_data[i] = adata[i];
        }

        // Инициализируем новые элементы (если размер увеличивается)
        for (size_t i = asize; i < size; ++i) {
            new_data[i] = Data(); // значение по умолчанию для типа Data
        }

        // Освобождаем старую память и обновляем указатели
        delete[] adata;
        adata = new_data;
        asize = size;
        acapacity = new_capacity;
    }
    return;
}