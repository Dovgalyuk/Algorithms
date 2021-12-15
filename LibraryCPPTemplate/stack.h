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

    // Помещает данные в верхнюю часть стека
    // Should be O(1) on average
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
    // Should be O(1)
    void pop()
    {
        if (!empty()){
            list->erase(list->first());
        }
    }

    // Возвращает значение true, если стек пуст
    bool empty()
    {
        return !list->first();
    }

private:
    // private data should be here
    List<Data> *list;
};

#endif