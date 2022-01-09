#ifndef STACK_H
#define STACK_H
#include "list.h"

template <typename Data> class Stack
{
public:
    // Создает пустой стек
    Stack()
    {
        list = new List<Data>;
    }

    // Удаляет стек
    ~Stack()
    {
        delete list;
    }

    // Помещает данные на вершину стека
    // В среднем должно быть O(1)
    void push(Data data)
    {
        list->insert(data);
    }

    // Извлекает последний элемент из стека
    Data get()
    {
       return list->first()->data();
    }

    // Удаляет последний элемент из стека
    // Должно быть О(1)
    void pop()
    {
        if (!empty()){
            list->erase(list->first());
        }
    }

    // Возвращает true, если стек пуст
    bool empty()
    {
        return !list->first();
    }

private:
    // приватные данные должны быть здесь
    List<Data> *list;
};

#endif
