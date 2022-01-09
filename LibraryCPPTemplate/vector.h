#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector(): length(0), capacity(0), vector(nullptr) // длина = 0, объем = 0, вектор = 0
    {
    }

    // Deletes vector structure and internal data
    ~Vector()
    {
        delete []vector;
    }

    // Извлекает элемент вектора с указанным индексом
    Data get(size_t index) const
    {
        return vector[index]; // возвращает данные, которые хранятся под индексом
    }

    // Присваивает элемент вектора с указанным индексом
    void set(size_t index, Data value)
    {
        if(index <= length) //Если индекс меньше или равно длины..
            vector[index] = value; // ..присваем под индексом значение
    }

    // Получаеем текущий размер вектора
    size_t size() const
    {
        return length; //возвращаем длину
    }

    // Изменяет размер вектора
    // Should be O(1) on average
    void resize(size_t newSize)
    {
        if(capacity < newSize) {
            increaseCapacity(newSize); //Увеличение объема
            Data* newVector = new Data[capacity]; //Создаем новый массив данных
            copyArray(newVector, this->size()); //Копируем массив
            delete []vector;//Удаляем данные
            vector = newVector;//Вектору присваиваем новое значение
        }
        length = newSize;
    }


private:
    // private data should be here


    void copyArray(Data* newVector, size_t size){
        for (int i = 0; i < size; ++i)
            newVector[i] = vector[i];
    }

    void increaseCapacity(size_t size) {
        if (capacity >= size) //Если объем больше или равно размера
            return;// то выходим
        if (capacity == 0) //если объем равен 0
            capacity = 1; //то присваиваем 1
        while (capacity < size) //Пока объем меньше размера
            capacity *= capacity_increase; //Объем умножаем на 2
    }

    size_t length;
    size_t capacity;
    const int capacity_increase = 2;
    Data* vector;
};

#endif

