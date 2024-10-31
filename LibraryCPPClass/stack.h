#ifndef STACK_H
#define STACK_H

#include "list.h"

class Stack
{
public:
    // Создает пустой стек
    Stack();

    // Копирующий конструктор
    Stack(const Stack &a);

    // Оператор присваивания
    Stack &operator=(const Stack &a);

    // Деструктор очищает стек
    ~Stack();

    // Добавляет элемент на вершину стека
    void push(Data data);

    // Возвращает последний элемент (на вершине стека)
    Data get() const;

    // Удаляет последний элемент с вершины стека
    void pop();

    // Проверяет, пуст ли стек
    bool empty() const { return list_.first() == nullptr; }

private:
    List list_; // Внутренний список для хранения данных стека
};

#endif
