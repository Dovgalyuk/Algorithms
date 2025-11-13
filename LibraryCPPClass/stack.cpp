#include "stack.h"
#include <stdexcept>

Stack::Stack()
{
}

Stack::Stack(const Stack &a) : stack_data(a.stack_data)
{
    // implement or disable this function
}

Stack &Stack::operator=(const Stack &a)
{
    // implement or disable this function
    if (this != &a) {
        stack_data = a.stack_data;
    }
    return *this;
}

Stack::~Stack()
{
}

void Stack::push(Data data)
{
    size_t old_size = stack_data.size();
    stack_data.resize(old_size + 1);
    stack_data.set(old_size, data);
}

Data Stack::get() const
{
    if (stack_data.size() == 0) {
        throw std::runtime_error("Stack is empty");
    }
    return stack_data.get(stack_data.size() - 1);
}

void Stack::pop()
{
    if (stack_data.size() == 0) {
        throw std::runtime_error("Stack is empty");
    }
    stack_data.resize(stack_data.size() - 1);
}

bool Stack::empty() const
{
    return stack_data.size() == 0;
}
