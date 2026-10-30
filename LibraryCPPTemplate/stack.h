#ifndef STACK_TEMPLATE_H
#define STACK_TEMPLATE_H

#include "list.h"
#include <cstddef>
#include <stdexcept>

// Стек LIFO, реализованный на основе односвязного List.
template <typename Data>
class Stack
{
private:
    List<Data> elements;

public:
    Stack() = default;
    Stack(const Stack&) = default;
    Stack(Stack&&) noexcept = default;
    Stack& operator=(const Stack&) = default;
    Stack& operator=(Stack&&) noexcept = default;
    ~Stack() = default;

    // Кладёт значение на вершину за O(1).
    void push(Data value) { elements.insert(value); }

    // Возвращает значение на вершине без удаления.
    Data get() const
    {
        if (empty())
            throw std::out_of_range("Stack is empty");
        return elements.first()->data();
    }

    // Удаляет вершину за O(1).
    void pop()
    {
        if (empty())
            throw std::out_of_range("Stack is empty");
        elements.erase_first();
    }

    bool empty() const { return elements.empty(); }
    std::size_t size() const { return elements.size(); }
};

#endif
