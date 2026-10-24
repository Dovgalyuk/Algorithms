
#include "stack.h"
#include <stdexcept>

// Создание пустого стека
Stack::Stack()
{
}

// Копирование стека
Stack::Stack(const Stack &a) : list_(a.list_)
{
}

// Присваивание одного стека другому
Stack &Stack::operator=(const Stack &a)
{
    if (this != &a)
        list_ = a.list_;

    return *this;
}

// Удаление стека
Stack::~Stack()
{
}

// Добавление элемента на вершину
void Stack::push(Data data)
{
    list_.insert(data);
}

// Получение верхнего элемента
Data Stack::get() const
{
    if (empty())
        throw std::out_of_range("Stack is empty");

    return list_.first()->data();
}

// Удаление верхнего элемента
void Stack::pop()
{
    if (empty())
        throw std::out_of_range("Stack is empty");

    list_.erase_first();
}

// Проверка стека на пустоту
bool Stack::empty() const
{
    return list_.first() == nullptr;
}
