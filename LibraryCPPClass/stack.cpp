#include "stack.h"
#include <stdexcept>

Stack::Stack() = default;

Stack::Stack(const Stack &a)
    : values(a.values)
{
}

Stack &Stack::operator=(const Stack &a)
{
    if (this != &a)
        values = a.values;

    return *this;
}

Stack::~Stack() = default;

void Stack::push(Data data)
{
    values.insert(data);
}

Data Stack::get() const
{
    if (empty())
        throw std::out_of_range("Stack is empty");

    return values.first()->data();
}

void Stack::pop()
{
    if (!empty())
        values.erase_first();
}

bool Stack::empty() const
{
    return values.first() == nullptr;
}
