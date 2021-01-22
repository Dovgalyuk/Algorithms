

#ifndef VECTORQUEUE_VECTOR_H
#define VECTORQUEUE_VECTOR_H

#include <cstdio>
#include <iostream>

template<typename T>
class Vector{
private:
    //[_capacity] - вместимость вектора.
    size_t _capacity;
    //[_size] - количество ячеек, занятых в массиве. Размер вектора.
    size_t _size;
    //[_array] - массив, в котором храняться данные.
    T* _array;
public:
    //Стандартный конструктор.
    Vector() : _size(0), _capacity(1), _array(new T[_capacity]){}

    //Конструктор, с указанием начальной вместимости вектора.
    explicit Vector(size_t init_capacity) : _size(0), _capacity(init_capacity), _array(new T[_capacity]){}

    //Деструктор, освобождающий память, выделенную под массив.
    ~Vector(){
        delete [] _array;
    }
    //Добавление нового элемента в конец вектора.
    void push_back(const T& value){
        if (_size < _capacity){
            //Если вместимости вектора хватает, запись в ячейку массива по индексу.
            _array[_size] = value;
            //Увеличиваем текущий размер на единицу.
            ++_size;
        } else {
            //Если места не хватает, создаётся новый массив с достаточной вместимостью.
            T* new_array = new T[_capacity * 2];
            //И заполняется поэлементнно, путём копирования из старого массива.
            for (size_t i = 0; i < _capacity; ++i) {
                new_array[i] = _array[i];
            }
            //Увеличиваем вместимость вектора.
            _capacity = _capacity * 2;
            //Освобождаем память, выделенную под предыдущий массив.
            delete [] _array;
            //Присваеваем новый мыссив как основной.
            _array = new_array;
            //Открепляем указатель. (Технически, это делать не надо, ибо локальная переменная. Но segmentation fault случается, если указатель явно не занулить.)
            new_array = nullptr;
            //Добавляем новое значение в расширившийся вектор.
            push_back(value);
        }
    }
    //Форматированный вывод вектора. Формат: (i0, i1, ..., in)
    void print(){
        std::cout << "(";
        for (size_t i = 0; i < _size; ++i){
            std::cout << _array[i];
            if (i + 1 < _size) {
                std::cout << ", ";
            }
        }
        std::cout << ")" << std::endl;
    }
    //Перегрузка оператора [get()].
    T& operator[](const size_t& index){
        if (index < 0 || index >= _size){
            //Исключение о том, что в массиве нет такого индекса.
            throw std::invalid_argument("Index out of range");
        } else {
            //Возврат значения по индексу.
            return _array[index];
        }
    }
    //Перегрузка оператора [get()].
    T& operator[](const size_t& index) const {
        if (index < 0 || index >= _size){
            //Исключение о том, что в массиве нет такого индекса.
            throw std::invalid_argument("Index out of range");
        } else {
            //Возврат значения по индексу.
            return _array[index];
        }
    }
    //Функция [get()].
    T& get(const size_t& index) {
        if (index < 0 || index >= _size){
            //Исключение о том, что в массиве нет такого индекса.
            throw std::invalid_argument("Index out of range");
        } else {
            //Возврат значения по индексу.
            return _array[index];
        }
    }
    //Удаление элемента по индексу.
    void erase(const size_t& index) {
        if (index < 0 || index >= _size){
            throw std::invalid_argument("Index out of range");
        } else {
            //"Затирание" элемента, путём смещения оставшихся элементов.
            for (size_t i = index; i < _size - 1; ++i) {
                _array[i] = _array[i + 1];
            }
            //Уменьшение размеров вектора.
            --_size;
        }
    }
    //Проверка на наличие элемента в векторе.
    bool contents(const T& value) {
        //Банальный обход вектора и возврат true, если [vector[i]] равен [value].
        for (size_t i = 0; i < _size; ++i) {
            if ( _array[i] == value ) {
                return true;
            }
        }
        return false;
    }
    //Очистка вектора
    void clear() {
        //Де-факто, просто указание на то, что размер вектора равен нулю.
        //В случае записи значения в вектор, значение в ячейках перезаписывается и нет нужды в удалении -> создании нового массива.
        _size = 0;
    }

    //Геттер [_size]
    size_t size(){return _size;}

    //true если вектор полностью заполнен, false иначе
    bool is_full(){return _size == _capacity;}

};

#endif //VECTORQUEUE_VECTOR_H
