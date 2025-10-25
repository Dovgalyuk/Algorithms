#ifndef STACK_TEMPLATE_H
#define STACK_TEMPLATE_H

#include <string>
#include <stdexcept>
#include <vector.h>
template <typename Data> class Stack
{
private:
    // private data should be here
    Vector<Data> box;
public:
    // Creates empty stack
    Stack()
    {
    }

    // copy constructor
    Stack(const Stack &a) :box(a.box)
    {
        // implement or disable this function
    }

    // assignment operator
    Stack &operator=(const Stack &a)
    {
        // implement or disable this function
        box = a.box;
        return *this;
    }

    // Deletes the stack
    ~Stack()
    {
    }

    // Pushes data on top of the stack
    // Should be O(1) on average
    void push(Data data)
    {
        box.resize(box.size() + 1);
        box.set(box.size() - 1, data);
    }

    // Retrieves the last element from the stack
    Data get() const
    {
        if (box.size() == 0)
        {
            throw std::out_of_range("ERROR: index out of range");
        }
        return box.get(box.size() - 1);
    }

    // Removes the last element from the stack
    // Should be O(1)
    void pop()
    {
        if (box.size() == 0)
        {
            throw std::out_of_range("Cannot pop from empty stack");
        }
        box.resize(box.size() - 1);
    }

    // Returns true if the stack is empty
    bool empty() const
    {
        return box.size() == 0;
    }

};

#endif
