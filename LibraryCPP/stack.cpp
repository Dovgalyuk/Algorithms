#include <cstddef>
#include "stack.h"
#include "list.h"

using namespace std;

struct ListItem
{
    Data data;
    ListItem* next;
};

struct List
{
    ListItem* begin;
    ListItem* end;
};

struct Stack
{
    List* top;
};

Stack* stack_create()
{
    Stack* stack = new Stack;
    stack->top = list_create();
    return stack;
}

void stack_delete(Stack* stack)
{
    list_erase_first(stack->top);
    list_delete(stack->top);
    delete stack;
}

void stack_push(Stack* stack, Data newData)
{
    // ������� ����� ������� ������
    ListItem* newItem = new ListItem;
    newItem->data = newData;
    newItem->next = nullptr;

    // ���������, ���� �� ����
    if (stack->top->begin == nullptr)
    {
        // ���� ���� ����, ������������� ������ � ����� ������ �� ����� �������
        stack->top->begin = newItem;
        stack->top->end = newItem;
    }
    else
    {
        // ����� ��������� ����� ������� � ������ ������
        newItem->next = stack->top->begin;
        stack->top->begin = newItem;
    }
}

Data stack_get(const Stack* stack)
{
    return list_item_data(list_first(stack->top));
}

void stack_pop(Stack* stack)
{
    // ��������� ��������� �� ��������� �������
    ListItem* nextItem = stack->top->begin->next;

    // ������� ������� �� ������ ������
    delete stack->top->begin;

    // ��������� ������ ������
    stack->top->begin = nextItem;

    // ���� ���� ���� ������, ��������� � ����� ������
    if (stack->top->begin == nullptr)
    {
        stack->top->end = nullptr;
    }
}

bool stack_empty(const Stack* stack)
{
    return stack->top;
}
