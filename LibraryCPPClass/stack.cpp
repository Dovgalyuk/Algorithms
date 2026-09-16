#include "stack.h"

Stack::Stack()
{
}

Stack::Stack(const Stack &a) : helper(a.helper)
{
}

Stack &Stack::operator=(const Stack &a)
{
    if (this != &a)
    {
        helper = a.helper;
    }
    return *this;
}

Stack::~Stack()
{
}

void Stack::push(Data data)
{
    helper.push_back(data);
}

Data Stack::get() const
{
    if (helper.size() == 0)
    {
        throw std::out_of_range("Stack::get: stack is empty");
    }
    return helper.get(helper.size() - 1);
}

void Stack::pop()
{
    if (helper.size() == 0){
        throw std::out_of_range("Stack::pop: stack is empty");
    }
    helper.resize(helper.size() - 1);
}

bool Stack::empty() const
{
    return helper.size() == 0;
}
