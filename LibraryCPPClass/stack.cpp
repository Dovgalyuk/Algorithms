#include "stack.h"

Stack::Stack()
{
}


Stack::~Stack()
{
}

void Stack::push(Data data)
{
    m_data.insert(data);
}

Data Stack::get() const
{
    return this->m_data.first()->data();
}

void Stack::pop()
{
    m_data.erase_first();
}

bool Stack::empty() const
{
    return !m_data.first();
}
