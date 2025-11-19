#include "stack.h"
#include "list.h"

Stack::Stack() : list() {}

Stack::Stack(const Stack &a) : list(a.list)
{
    // implement or disable this function
}

Stack &Stack::operator=(const Stack &a)
{
    // implement or disable this function
    if (this != &a)
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
    List::Item *f = const_cast<List&>(list).first();
    return f ? f->data() : Data();
}

void Stack::pop()
{
    list.erase_first();
}

bool Stack::empty() const
{
    return list.first() == nullptr;
}
