#ifndef STACK_TEMPLATE_H
#define STACK_TEMPLATE_H

#include "list.h"

template <typename Data>
class Stack
{
public:
    // Creates empty stack
    Stack() : mList(), mSize(0)
    {
    }

    // copy constructor
    Stack(const Stack &a) : Stack()
    {
        // implement or disable this function
        mList = a.mList;
        mSize = a.mSize;
    }

    // assignment operator
    Stack &operator=(const Stack &a)
    {
        // implement or disable this function
        mList = a.mList;
        mSize = a.mSize;
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
        mList.insert(data);
        mSize++;
    }

    // Retrives the last element from the stack
    Data get() const
    {
        return mList.first()->data();
    }

    // Removes the last element from the stack
    // Should be O(1)
    void pop()
    {
        mList.erase_first();
        mSize--;
    }

    // Returns true if the stack is empty
    bool empty() const
    {
        return mList.empty() && mSize == 0;
    }

private:
    // private data should be here
    List<Data> mList;
    std::size_t mSize;
};

#endif
