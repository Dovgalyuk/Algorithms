#include "stack.h"
#include <stdexcept>

Stack::Stack() = default;
Stack::Stack(const Stack &a) = default;
Stack &Stack::operator=(const Stack &a) = default;
Stack::~Stack() = default;

void Stack::push(Data data)
{
    list_.insert(data);
}

Data Stack::get() const
{
    if (empty()) throw std::out_of_range("Stack is empty");
    return list_.first()->data();
}

void Stack::pop()
{
    if (empty()) throw std::out_of_range("Stack is empty");
    list_.erase_first();
}

bool Stack::empty() const
{
    return list_.first() == nullptr;
}
