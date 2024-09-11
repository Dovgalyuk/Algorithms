#include "stack.h"
#include <stdexcept>

Stack::Stack() : list_(new List()) 
{
}

Stack::Stack(const Stack &a) : list_(new List(*a.list_)) 
{
    // implement or disable this function
}

Stack &Stack::operator=(const Stack &a)
{
    if (this != &a) {
        delete list_;
        list_ = new List(*a.list_);
    }
    return *this;
}

Stack::~Stack()
{
    delete list_;
}

void Stack::push(Data data)
{
    list_->insert(data);
}

Data Stack::get() const
{
    if (empty()) {
        throw std::runtime_error("Stack is empty");
    }
    return list_->first()->data();
}

void Stack::pop()
{
    if (empty()) {
        throw std::runtime_error("Stack is empty");
    }
    list_->erase_first();
}

bool Stack::empty() const
{
    return (list_->first() == nullptr);
}
