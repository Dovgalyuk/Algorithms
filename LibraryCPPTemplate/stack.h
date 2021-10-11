#ifndef STACK_H
#define STACK_H
#include <vector.h>

template <typename Data>
class Stack
{
public:
    // Creates empty stack
    Stack()
    {
        vector =  new Vector<Data>();
        lastIndex = -1;
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
        lastIndex += 1;       
        vector->resize(lastIndex + 1);
        vector->set(lastIndex, data);
         
    }

    // Retrives the last element from the stack
    Data get() const
    {
        return vector->get(lastIndex);
    }

    // Removes the last element from the stack
    // Should be O(1)
    void pop()
    {
        lastIndex -=1;
    }

    // Returns true if the stack is empty
    bool empty() const
    {
        return lastIndex < 0;
    }

private:
    Vector<Data> *vector;
    int lastIndex;
    // private data should be here
};

#endif
