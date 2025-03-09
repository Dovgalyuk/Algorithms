#include "stack.h"
#include "list.h"

struct Stack
{
    List* list; 
};

// Создание стека
Stack *stack_create()
{
    Stack* stack = new Stack;
    stack->list = list_create();
    return stack;
}

// Удаление стека
void stack_delete(Stack *stack)
{
    list_delete(stack->list);
    delete stack;
}

// Добавление элемента на вершину стека
void stack_push(Stack *stack, Data data)
{
    list_insert(stack->list, data);
}

// Получение элемента с вершины стека
Data stack_get(const Stack *stack)
{
    ListItem* first = list_first(stack->list);
    if (!first) {
        return 0;
    }
    return list_item_data(first);
}

// Удаление элемента с вершины стека
void stack_pop(Stack *stack)
{
    list_erase_first(stack->list);
}

// Проверка, пуст ли стек
bool stack_empty(const Stack *stack)
{
    return (list_first(stack->list) == nullptr);
}
