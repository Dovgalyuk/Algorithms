#ifndef STACK_TEMPLATE_H
#define STACK_TEMPLATE_H

#include "list.h"

template <typename Data> class Stack
{
public:
    // Creates empty stack
    Stack() {}

    // copy constructor
    Stack(const Stack& other) : list_(other.list_) {}

    // assignment operator
    Stack& operator=(const Stack& other)
    {
        if (this != &other)
            list_ = other.list_;
        return *this;
    }

    // Deletes the stack
    ~Stack() {}

    // Pushes data on top of the stack
    // Should be O(1) on average
    void push(Data data)
    {
        list_.insert(data);
    }   

    // Retrieves the last element from the stack
    Data get() const
    {
        if (empty()) throw std::runtime_error("Stack is empty");
        return list_.first()->data();
    }

    // Removes the last element from the stack
    // Should be O(1)
    void pop()
    {
        if (empty()) throw std::runtime_error("Stack is empty");
        list_.erase_first();
    }

    // Returns true if the stack is empty
    bool empty() const 
    { 
        return list_.first() == nullptr;
    }

private:
    // private data should be here
    List<Data> list_;
};

#endif
