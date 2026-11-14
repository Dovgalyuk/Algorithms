#include "stack.h"
#include <stdexcept>

Stack::Stack() = default;

Stack::Stack(const Stack& a) : list(a.list)
{
}

Stack& Stack::operator=(const Stack& a)
{
    if (this != &a)
    {
        list = a.list;
    }

    return *this;
}

Stack::~Stack() = default;

void Stack::push(Data data)
{
    list.insert(data);
}

Data Stack::get() const
{
    List::Item* item = const_cast<List&>(list).first();

    if (item == nullptr)
    {
        throw std::runtime_error("Stack is empty");
    }

    return item->data();
}

void Stack::pop()
{
    if (list.first() == nullptr)
    {
        throw std::runtime_error("Stack is empty");
    }

    list.erase_first();
}

bool Stack::empty() const
{
    return const_cast<List&>(list).first() == nullptr;
}