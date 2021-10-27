#include "stack.h"
#include "list.h"

struct ListItem
{
    ListItem* next;
    void clear()
    {
        if (next != nullptr)
        {
            next->clear();
            delete next;
        }
    }
};

struct List   
{             
    ListItem* head;
    ~List()
    {
        if (head != nullptr)
            head->clear();
        delete head;
    }
};

struct Stack
{
    List* stack;
    Stack()
    {
        stack = list_create();
    }
    ~Stack()
    {
        delete stack;
    }
};

Stack* stack_create()
{
    return new Stack;
}

void stack_delete(Stack* stack)
{
    delete stack;
}

void stack_push(Stack* stack, Data data)
{
    list_insert(stack->stack, data);
}

Data stack_get(const Stack* stack)
{
    return list_item_data(list_first(stack->stack));
}

void stack_pop(Stack* stack)
{
    if (stack_empty(stack) == false)
    {
        list_erase_first(stack->stack);
    }
}

bool stack_empty(const Stack* stack)
{
        return list_first(stack->stack) == nullptr;
}
