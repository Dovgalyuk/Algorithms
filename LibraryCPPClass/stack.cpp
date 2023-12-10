#include "stack.h"
#include "list.cpp"

// Creates empty stack
Stack::Stack() : dataList() {}

// Deletes the stack
Stack::~Stack() {}

// Pushes data on top of the stack
void Stack::push(Data data)
{
    dataList.insert(data);
}

// Retrieves the last element from the stack
Data Stack::get() const
{
    if (dataList.first() != nullptr)
        return dataList.first()->data();
    else
        return Data();  // Return a default-constructed Data object if the stack is empty
}

// Removes the last element from the stack
void Stack::pop()
{
    dataList.erase_first();
}

// Returns true if the stack is empty
bool Stack::empty() const
{
    return dataList.first() == nullptr;
}
