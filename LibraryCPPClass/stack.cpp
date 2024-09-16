#include "stack.h"

Stack::Stack() {
}

Stack::Stack(const Stack &a) {
    _stack = a._stack;
}

Stack &Stack::operator=(const Stack &a) {
    return *this;
}

Stack::~Stack(){
    while (!_stack.empty()) {
        _stack.pop();
    }
}

void Stack::push(Data data){
    _stack.push(data);
}

Data Stack::get() const {
    return _stack.top();
}

void Stack::pop(){
    _stack.pop();
}

bool Stack::empty() const
{
    return _stack.empty();
}
