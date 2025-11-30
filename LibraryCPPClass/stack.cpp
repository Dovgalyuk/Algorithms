#include "stack.h"
#include "vector.h"
#include <stdexcept>

Stack::Stack()
{
}

Stack::Stack(const Stack& a)
{
    vec = a.vec;
}

Stack& Stack::operator=(const Stack& a)
{
    vec = a.vec;
    return *this;
}

Stack::~Stack()
{
}

void Stack::push(Data data)
{
    vec.resize(vec.size() + 1);
    vec.set(vec.size() - 1, data);
}

Data Stack::get() const
{
    if (vec.size() == 0) throw std::runtime_error("stack_get on empty stack");
    return vec.get(vec.size() - 1);
}

void Stack::pop()
{
    if (vec.size() == 0) throw std::runtime_error("stack_pop on empty stack");
    vec.resize(vec.size() - 1);
}

bool Stack::empty() const
{
    return vec.size() == 0;
}

size_t Stack::size() const {
    return vec.size();
}
