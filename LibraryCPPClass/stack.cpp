#include "stack.h"

#include <stdexcept>

Stack::Stack()
{
}

Stack::Stack(const Stack& a)
    : list_(a.list_)
{
}

Stack& Stack::operator=(const Stack& a)
{
    if (this != &a)
        list_ = a.list_;
    return *this;
}

Stack::~Stack()
{
}

void Stack::push(Data data)
{
    list_.insert(data);
}

Data Stack::get() const
{
    const List::Item* top = list_.first();
    if (top == nullptr)
        throw std::out_of_range("Stack::get: stack is empty");
    return top->data();
}

void Stack::pop()
{
    if (empty())
        throw std::out_of_range("Stack::pop: stack is empty");
    list_.erase_first();
}

bool Stack::empty() const
{
    return list_.first() == nullptr;
}