#ifndef STACK_TEMPLATE_H
#define STACK_TEMPLATE_H

#include "vector.h"

template <typename Data> class Stack
{
public:
    // Creates empty stack
    Stack()
    {
        // Вектор сам создает контейнер по дефолту
    }

    // copy constructor
    Stack(const Stack &a)
    {
        mContainer = a.mContainer;
    }

    // assignment operator
    Stack &operator=(const Stack &a)
    {
        if (this != &a)
            mContainer = a.mContainer;
        return *this;
    }

    // Deletes the stack
    ~Stack()
    {
        // Деструктор использующегося вектора сам очищает память
    }

    // Pushes data on top of the stack
    // Should be O(1) on average
    void push(Data data)
    {
        size_t currentSize = mContainer.size();
        mContainer.resize(currentSize + 1);

        mContainer.set(currentSize, data);
    }

    // Retrieves the last element from the stack
    Data get() const
    {
        size_t currentSize = mContainer.size();
        if (currentSize > 0)
            return mContainer.get(currentSize - 1);

        return Data();
    }

    // Removes the last element from the stack
    // Should be O(1)
    void pop()
    {
        size_t currentSize = mContainer.size();
        if (currentSize > 0)
           mContainer.resize(currentSize - 1);
    }

    // Returns true if the stack is empty
    bool empty() const
    {
        return mContainer.size() == 0;
    }

private:
    Vector<Data> mContainer;
};

#endif
