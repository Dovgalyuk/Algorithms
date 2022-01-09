#ifndef STACK_H
#define STACK_H

#include "vector.h"
#include "cstddef"

template <typename Data> class Stack
{
public:
    // Создаем пустой стек
    Stack() : vector(new Vector<Data>())
    {

    }

    // Deletes the stack
    ~Stack()
    {
        delete vector;
    }

    // Помещает данные на вершину стека
    // Should be O(1) on average
    void push(Data data)
    {
        vector->resize(vector->size() + 1); // Увеличиваем размер вектора на 1
        vector->set(vector->size() - 1, data); // Добавляем в конец
    }

    // Извлекает последний элемент из стека
    Data get() const
    {
        return vector->get(vector->size() - 1); // Берем последний элемент
    }

    // Удаляет последний элемент из стека
    // Should be O(1)
    void pop()
    {
        vector->resize(vector->size() - 1); // Уменьшаем размер на 1
    }

    // Возвращает значение true, если вектор пустой
    bool empty() const
    {
        return vector->size() == 0;
    }

private:
    // private data should be here
    Vector<Data>* vector = nullptr;
};

#endif