#include "stack.h"
#include <stdexcept>
using namespace std;
Stack::Stack()
{
}

Stack::Stack(const Stack &a)
{
    (void) a;
    // implement or disable this function
}

Stack &Stack::operator=(const Stack &a)
{
    (void)a;
    // implement or disable this function
    return *this;
}

Stack::~Stack()
{
}

void Stack::push(Data data)
{
    vec_.resize(vec_.size() + 1);
    vec_.set(vec_.size() - 1, data);
}

Data Stack::get() const
{
    if (vec_.size() == 0) {
        throw ::out_of_range("stak pust");
    }

    return vec_.get(vec_.size() - 1);
}

void Stack::pop()
{
    if (vec_.size() == 0) {
        throw ::out_of_range("maliy rashod steka");
    }

    vec_.resize(vec_.size() - 1);

}

bool Stack::empty() const
{
    return vec_.size() == 0;
}
