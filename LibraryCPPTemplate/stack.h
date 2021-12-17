#ifndef STACK_H
#define STACK_H
#include "vector.h"

template <typename Data>
class Stack : Vector<Data> {
public:

    // Creates empty stack
    Stack() : Vector<Data>() {}

    // Deletes the stack
    ~Stack() = default;

    // Pushes data on top of the stack
    // Should be O(1) on average
    void push(Data data) {
        this->resize(this->length + 1);
        this->data[this->length - 1] = data;
    }

    // Retrives the last element from the stack
    Data get() const {
        return this->data[this->length - 1];
    }

    // Removes the last element from the stack
    // Should be O(1)
    void pop() {
        this->resize(this->length - 1);
    }

    // Returns true if the stack is empty
    bool empty() const {
        return this-> length == 0;
    }
};

#endif