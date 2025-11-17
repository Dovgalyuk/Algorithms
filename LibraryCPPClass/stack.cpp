#include "stack.h"
#include <stdexcept>


using namespace std;


Stack::Stack()
{
}

Stack::Stack(const Stack &a)
{
    // implement or disable this function
}

Stack &Stack::operator=(const Stack &a)
{
    // implement or disable this function
    if (this != &a)
        helper = a.helper;
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
    if (helper.size() > 0) 
        return helper.get(helper.size() - 1);
    throw out_of_range("no elements");
}

void Stack::pop()
{
    if (helper.size() > 0)
        helper.resize(helper.size() - 1);
    else
        throw out_of_range("no elements");

}

bool Stack::empty() const
{
    return helper.size() == 0;
}
