#include "stack.h"
#include "list.h"

// Стек, реализованный на основе двусвязного списка
struct Stack
{
    List *list; // Указатель на список, хранящий элементы стека
};

// Создание пустого стека
Stack *stack_create()
{
    Stack *stack = new Stack;
    stack->list = list_create();
    return stack;
}

// Удаление стека и освобождение памяти
void stack_delete(Stack *stack)
{
    if (!stack)
        return;
    list_delete(stack->list);
    delete stack;
}

// Помещение элемента на вершину стека
void stack_push(Stack *stack, Data data)
{
    if (!stack)
        return;
    list_insert(stack->list, data);
}

// Получение значения с вершины стека
Data stack_get(const Stack *stack)
{
    if (!stack)
        return (Data)0;
    ListItem *first = list_first(stack->list);
    if (!first)
        return (Data)0;
    return list_item_data(first);
}

// Удаление элемента с вершины стека
void stack_pop(Stack *stack)
{
    if (!stack)
        return;
    list_erase_first(stack->list);
}

// Проверка стека на пустоту
bool stack_empty(const Stack *stack)
{
    if (!stack)
        return true;
    return list_first(stack->list) == nullptr;
}
