#ifndef STACK_TEMPLATE_H
#define STACK_TEMPLATE_H

template <typename Data> class Stack
{
public:
    // Creates empty stack
    Stack()
    {
        this->top = nullptr;
        this->next = nullptr;
    }

    // copy constructor
    //Stack(const Stack &a)
    //{
    //    // implement or disable this function
    //}

    // assignment operator
    //Stack &operator=(const Stack &a)
    //{
    //    // implement or disable this function
    //}

    // Deletes the stack
    ~Stack()
    {
        Stack<Data> *curr = top;
        while (curr != nullptr) {
            Stack<Data> *next = curr->next;
            delete curr;
            curr = next;
        }
    }

    // Pushes data on top of the stack
    // Should be O(1) on average
    void push(Data data)
    {
        Stack<Data> *newItem = new Stack<Data>;
        newItem->data = data;
        newItem->next = this->top;
        this->top = newItem;
    }

    // Retrives the last element from the stack
    Data get() const
    {
        if (this->top == nullptr)
        {
            return Data();
        }
        return this->top->data;
    }

    // Removes the last element from the stack
    // Should be O(1)
    void pop()
    {
        if (this->top != nullptr)
        {
            Stack<Data> *item = this->top;
            this->top = item->next;
            delete item;
        }
    }

    // Returns true if the stack is empty
    bool empty() const
    {
        return this->top == nullptr;
    }

private:
    // private data should be here
    Data data;
    Stack<Data> *next;
    Stack<Data> *top;
};

#endif
