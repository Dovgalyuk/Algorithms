#ifndef STACK_TEMPLATE_H
#define STACK_TEMPLATE_H

#include "vector.h"

template <typename Data> class Stack
{
public:
    // Creates empty stack
    Stack()
    {
        vector = new Vector<Data>();
    }

    // Creates stack with default vales
    Stack(size_t size, Data default_value = Data())  // Data() represents the default value of type Data
    {
        vector = new Vector<Data>(size, default_value);
    }

    // copy constructor
    Stack(const Stack &a)
    {
        // implement or disable this function
        vector = new Vector<Data>(*(a.vector));
    }

    // assignment operator
    Stack &operator=(const Stack &a)
    {
        // implement or disable this function
        if (this != &a) {
            vector = new Vector<Data>(*(a.vector));
        }
        return *this;
    }

    // Deletes the stack
    ~Stack()
    {
        delete vector;
    }

    // Pushes data on top of the stack
    // Should be O(1) on average
    void push(Data data)
    {
        vector->push(data);
    }

    // Retrives the last element from the stack
    Data get() const
    {
        return vector->get(vector->size() - 1);
    }

    // Removes the last element from the stack
    // Should be O(1)
    void pop()
    {
        vector->pop();
    }

    // Returns true if the stack is empty
    bool empty() const
    {
        return vector->size() == 0;
    }

private:
    // private data should be here
    Vector<Data> *vector;
};

#endif
