#include "stack.h"

Stack::Stack()
{
}

Stack::Stack(const Stack &a) : list(a.list)
{
    // implement or disable this function
}

Stack &Stack::operator=(const Stack &a)
{
    // implement or disable this function
    if (this == &a) return *this;
    list = a.list;
    return *this;
}

Stack::~Stack()
{
}

void Stack::push(Data data)
{
    list.insert(data);
}

Data Stack::get() const 
{
    List::Item* top = list.first();
    return top ? top->data() : Data();
}

void Stack::pop()
{
    list.erase_first();
}

bool Stack::empty() const
{
    return list.first() == nullptr;
}

void Stack::swap()
{
    list.swap_first_two();
}

void Stack::reverse()
{
    list.reverse();
}