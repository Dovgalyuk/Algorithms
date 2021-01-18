

#ifndef VECTORQUEUE_QUEUE_H
#define VECTORQUEUE_QUEUE_H

#include "Vector.h"

template<typename T>
class Queue{

    private:
    //[_inner_vector] - вектор, на основе которого сделана очередь.
    Vector<T>* _inner_vector;
    //[_head_position] - индекс первогоэлемента очереди.
    size_t _head_position;

    public:
    //Стандартный конструктор.
    Queue() : _inner_vector(new Vector<T>()), _head_position(0){}

    //Деструктор с удалением вектора.
    ~Queue() { delete _inner_vector;};

    //Операция вставки в конец очереди.
    //
    //Суть метода заключается в том, что мы отслеживаем позицию первого элемента в очереди, вместо прямого его удаления.
    //Когда происходит удаление из очереди, мы просто передвигаем этот индекс на единицу вперёд, если это возможно.
    //(Когда есть, что удалять. Т.е. когда размер вектора != позиции первого элемента очереди)
    //Когда же вектор заполнен, происходит перезаписывание вектора. Во время перезаписи перезаписываются только те элементы,
    //которые имеют смысл (Т.е. стоят "правее" первого элемента очереди). А индекс вершины очереди становиться = 0, потому что
    //в новом векторе больше не осталось ненужного мусора "слева".
    //Среднеее время исполнения = О(1) - просто вставка по индексу или + 1 к индексу первого элемента в очереди, или доступ к элементу по индексу.
    //Иногда будет происходить перезапись О(Размер вектора - Индекс первого элемента очереди).
    //При малом размере очереди О Перезаписи -> О(1).
    //При большом размере очереди необходимость перезаписи снижается, т.к. есть ещё место в буфере. Следовательно О Манипуляций -> О(1).
    void insert(const T& value){
        if (_inner_vector->is_full() && _head_position != 0){
            Vector<T>* new_inner_vector = new Vector<T>(_inner_vector->size());
            for (int i = _head_position; i < _inner_vector->size(); ++i){
                new_inner_vector->push_back(_inner_vector->get(i));
            }
            _head_position = 0;
            delete _inner_vector;
            _inner_vector = new_inner_vector;
        }
        _inner_vector->push_back(value);
    }

    //Удаление первого элемента очереди.
    void remove(){
        if (_inner_vector->size() != _head_position){++_head_position;}
        //_inner_vector.erase(0);
    }

    //Доступ к первому элементу очереди.
    T& get(){
        return _inner_vector->get(_head_position);
    }

    //Проверка, пуста ли очередь.
    bool empty(){
        return _inner_vector->size() == _head_position;
    }

    //Очистка очереди.
    void clear(){
        _inner_vector->clear();
    }

    //Геттер текущего размера очереди.
    size_t size(){return _inner_vector->size();}

};

#endif //VECTORQUEUE_QUEUE_H
