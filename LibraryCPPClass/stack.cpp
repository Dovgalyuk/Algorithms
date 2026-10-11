#include "stack.h"

Stack::Stack() {}
Stack::~Stack() {}

void Stack::push(Data data) {
    size_t current_size = v_.size();
    v_.resize(current_size + 1);
    v_.set(current_size, data);
}

Data Stack::get() const {
    return v_.get(v_.size() - 1);
}

void Stack::pop() {
    v_.resize(v_.size() - 1);
}

bool Stack::empty() const {
    return v_.size() == 0;
}
