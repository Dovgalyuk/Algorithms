#include "stack.h"

Stack::Stack() : m_list() {}

Stack::Stack(const Stack &a) : m_list(a.m_list) {}

Stack &Stack::operator=(const Stack &a)
{
    if (this != &a) {
        m_list = a.m_list;
    }
    return *this;
}

Stack::~Stack()
{
}

void Stack::push(Data data)
{
    m_list.insert(data);
}

Data Stack::get() const
{
    if (empty())
        throw std::runtime_error("Stack is empty");

    return m_list.first()->data();
}

void Stack::pop()
{
    if (empty())
        throw std::runtime_error("Stack is empty");

    m_list.erase_first();
}

bool Stack::empty() const
{
    return m_list.first() == nullptr;
}
