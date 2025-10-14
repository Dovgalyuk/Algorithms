#include "stack.h"
#include <stdexcept>

Stack::Stack() : sdata()
{
}

Stack::Stack(const Stack& a) : sdata(a.sdata)
{
    // implement or disable this function
}

Stack& Stack::operator=(const Stack& a)
{
    // implement or disable this function
    if (this != &a) {
        sdata = a.sdata;
    }
    return *this;
}

Stack::~Stack()
{
}

void Stack::push(Data data)
{
    // Используем resize и set для добавления элемента
    size_t current_size = sdata.size();
    sdata.resize(current_size + 1);
    sdata.set(current_size, data);
}

Data Stack::get() const
{
    if (sdata.size() == 0) {
        throw std::out_of_range("Stack is empty");
    }
    return sdata.get(sdata.size() - 1);
}

void Stack::pop()
{
    if (sdata.size() == 0) {
        throw std::out_of_range("Stack is empty");
    }
    sdata.resize(sdata.size() - 1);
}

bool Stack::empty() const
{
    return sdata.size() == 0;
}