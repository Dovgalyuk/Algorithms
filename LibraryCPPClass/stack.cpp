#include "stack.h"

Stack::Stack()
{}

Stack::Stack(const Stack &a) : vector_(a.vector_)
{}

Stack &Stack::operator=(const Stack &a)
{
    if (this != &a) {
        vector_ = a.vector_;
    }
    return *this;
}

Stack::~Stack()
{
    // Vector destructor handles cleanup automatically
}

void Stack::push(Data data)
{
    vector_.resize(vector_.size() + 1);
    vector_.set(vector_.size() - 1, data);
}

Data Stack::get() const
{
    if (vector_.size() == 0) {
        return Data();
    }
    return vector_.get(vector_.size() - 1);
}

void Stack::pop()
{
    if (vector_.size() > 0) {
        vector_.resize(vector_.size() - 1);
    }
}

bool Stack::empty() const
{
    return vector_.size() == 0;
}
