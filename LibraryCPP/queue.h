
#ifndef VECTORQUEUE_QUEUE_H
#define VECTORQUEUE_QUEUE_H

#include "Vector.h"

template<typename T>
class Queue{

    private:
    //[_inner_vector] - вектор, на основе которого сделана очередь.
    Vector<T> _inner_vector;

    public:
    //Стандартный конструктор.
    Queue() : _inner_vector(Vector<T>()){}

    //Деструктор с удалением вектора.
    ~Queue() = default;

    //Операция вставки в конец очереди.
    void insert(const T& value){
        _inner_vector.push_back(value);
    }

    //Удаление первого элемента очереди.
    void remove(){
        _inner_vector.erase(0);
    }

    //Доступ к первому элементу очереди.
    T& get(){
        return _inner_vector.get(0);
    }

    //Проверка, пуста ли очередь.
    bool empty(){
        return _inner_vector.size() == 0;
    }

    //Очистка очереди.
    void clear(){
        _inner_vector.clear();
    }

    //Геттер текущего размера очереди.
    size_t size(){return _inner_vector->size();}

};

#endif //VECTORQUEUE_QUEUE_H
