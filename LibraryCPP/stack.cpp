#include "stack.h"

template <typename T>
struct StackItem
{
    T data;
    StackItem<T> *next;
};

template <typename T>
struct Stack
{
    StackItem<T> *top;
};

template <typename T>
Stack<T>* stack_create()
{
    Stack<T> *newStack = new Stack<T>;
    newStack->top = nullptr;
    return newStack;
}

template <typename T>
void stack_delete(Stack<T> *stack)
{
    StackItem<T> *item = stack->top;
    while (item != nullptr)
    {
        StackItem<T> *next = item->next;
        delete item;
        item = next;
    }
    delete stack;
}

template <typename T>
void stack_push(Stack<T> *stack, T data)
{
    StackItem<T> *newItem = new StackItem<T>;
    newItem->data = data;
    newItem->next = stack->top;
    stack->top = newItem;
}

template <typename T>
T stack_get(const Stack<T> *stack)
{
    if (stack->top == nullptr)
    {
        return T();
    }
    return stack->top->data;
}

template <typename T>
void stack_pop(Stack<T> *stack)
{
    if (stack->top != nullptr)
    {
        StackItem<T> *item = stack->top;
        stack->top = item->next;
        delete item;
    }
}

template <typename T>
bool stack_empty(const Stack<T> *stack)
{
    return stack->top == nullptr;
}