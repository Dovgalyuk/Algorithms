#include "stack.h"
#include <stdexcept>

Stack::Stack() : _stack(new List()) {
}

Stack::Stack(const Stack &a) : _stack(new List(*a._stack)) {
}

Stack &Stack::operator=(const Stack &a) {
    if (this == &a) return *this;

    delete _stack;
    _stack = new List(*a._stack);
    return *this;
}

Stack::~Stack() {
    delete _stack;
}

void Stack::push(Data data) {
    _stack->insert(data);
}

Data Stack::get() const {
    if (empty()) {
        throw std::runtime_error("Stack is empty");
    }
    return _stack->first()->data();
}

void Stack::pop() {
    if (empty()) {
        throw std::runtime_error("Stack is empty");
    }
    _stack->erase_first();
}

bool Stack::empty() const {
    return _stack->first() == nullptr;
}