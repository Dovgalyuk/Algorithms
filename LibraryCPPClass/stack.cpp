#include "stack.h"

Stack::Stack() : sList() {}

Stack::Stack(const Stack &a) : sList(a.sList)
{
    // implement or disable this function
}

Stack &Stack::operator=(const Stack &a)
{
    if (this != &a)
    {
        sList = a.sList;
    }
    // implement or disable this function
    return *this;
}

Stack::~Stack() {}

void Stack::push(Data data)
{
    sList.insert(data);
}

Data Stack::get() const
{
    List::Item* top = sList.first();
    if(empty())
    {
        throw std::out_of_range("Stack is empty");
    }

    return top->data(   );
}

void Stack::pop()
{
    if (empty())
    {
        throw std::out_of_range("Stack is empty");
    }
    sList.erase_first();
}

bool Stack::empty() const
{
    return sList.first() == nullptr;
}
