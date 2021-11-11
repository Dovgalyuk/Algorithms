#ifndef STACK_H
#define STACK_H
#include "vector.h"
using namespace std;
template <typename Data> class Stack
{
public:
    // Creates empty stack
    Stack(): vec(new Vector<Data>())
    {
    }

    // Deletes the stack
    ~Stack()
    {
        delete vec;
    }

    // Pushes data on top of the stack
    // Should be O(1) on average
    void push(Data data)
    {
        vec->resize(vec->size() + 1);
        vec->set(vec->size() - 1, data);
    }

    // Retrives the last element from the stack
    Data get() const
    {
        return vec->get(vec->size() - 1);
    }

    // Removes the last element from the stack
    // Should be O(1)
    void pop()
    {
        vec->resize(vec->size() - 1);
    }

    // Returns true if the stack is empty
    bool empty() const
    {
        return vec->size() == 0;
    }

private:
    // private data should be here
    Vector<Data> *vec;
};

#endif
