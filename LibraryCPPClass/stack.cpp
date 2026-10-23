#include "stack.h"
#include <stdexcept>

Stack::Stack() : list_()
{
}

Stack::Stack(const Stack &a) : list_(a.list_)
{
    // implement or disable this function
}

Stack &Stack::operator=(const Stack &a)
{
    if (this == &a) {
        return *this;
    }
    list_ = a.list_;
    // implement or disable this function
    return *this;
}

Stack::~Stack()
{
}

void Stack::push(Data data)
{
    list_.insert(data);
}

Data Stack::get() const
{
    if (list_.first() == nullptr) {
        throw std::out_of_range("Stack::get: stack is emty");
    }
    return list_.first()->data();
}

void Stack::pop()
{
    if (list_.first() == nullptr) {
        throw std::out_of_range("Stack::get: stack is emty");
    }
    list_.erase_first();
}

bool Stack::empty() const
{
    return list_.first() == nullptr;
}
