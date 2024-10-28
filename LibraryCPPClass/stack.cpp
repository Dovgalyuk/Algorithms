#include "stack.h"
#include <stdexcept>

using namespace std;

Stack::Stack() : list_()
{
}

Stack::Stack(const Stack &a) : list_(a.list_)
{
    // implement or disable this function
}

Stack &Stack::operator=(const Stack &a)
{
    // implement or disable this function
    if(this != &a) {
        list_ = a.list_;
    }
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
    List::Item* top = list_.first();
    if(top) {
        return top->data();
    }
    throw runtime_error("Stack is empty");
}

void Stack::pop()
{
    if(list_.first()) {
        list_.erase_first();
    } else {
        throw runtime_error("Stack is empty");
    }
}

bool Stack::empty() const
{
    return list_.first() == nullptr;
}