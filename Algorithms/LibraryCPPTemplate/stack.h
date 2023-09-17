#ifndef STACK_TEMPLATE_H
#define STACK_TEMPLATE_H

template <typename Data> class Stack
{
public:
    // Creates empty stack
    Stack()
    {
    }

    // copy constructor
    Stack(const Stack &a)
    {
        // implement or disable this function
    }

    // assignment operator
    Stack &operator=(const Stack &a)
    {
        // implement or disable this function
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
    }

    // Retrives the last element from the stack
    Data get() const
    {
        return Data();
    }

    // Removes the last element from the stack
    // Should be O(1)
    void pop()
    {
    }

    // Returns true if the stack is empty
    bool empty() const
    {
        return true;
    }

private:
    // private data should be here
};

#endif
