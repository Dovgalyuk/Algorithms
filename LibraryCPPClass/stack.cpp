#include "stack.h"
#include <stdexcept>

Data Stack::get() const
{
    if (empty())
        throw std::out_of_range("Stack is empty");
    return list_.first()->data();
}

void Stack::pop()
{
    if (empty())
        throw std::out_of_range("Stack is empty");
    list_.erase_first();
}
