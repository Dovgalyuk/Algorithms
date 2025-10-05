#include <stdlib.h>
#include "stack.h"
#include "list.h"

typedef struct Stack {
    List* list;
} Stack;

Stack *stack_create(FFree f)
{
    // Выделение памяти
    Stack* new_stack = (Stack*)malloc(sizeof(Stack));
    if (new_stack == NULL) {
        return NULL;  
    }
    
    // Создание списка
    new_stack->list = list_create(f);
    if (new_stack->list == NULL) {
        free(new_stack);
        return NULL;
    }
    
    return new_stack;
}

void stack_delete(Stack *stack)
{
    if (stack == NULL) {
        return;  // Нечего удалять
    }
    
    // Удаление списка внутри стека
    list_delete(stack->list);
    
    free(stack);
}

void stack_push(Stack *stack, Data data)
{
    if (stack == NULL) {
        return;  
    }
    
    // Вставка эелемента в начало
    list_insert(stack->list, data);
}

Data stack_get(const Stack *stack)
{
    if (stack == NULL || stack->list == NULL) {
        return (Data)0;  
    }
    
    // первый элемент списка
    ListItem* first = list_first(stack->list);
    if (first == NULL) {
        return (Data)0;  
    }
    
    return list_item_data(first);
}

void stack_pop(Stack *stack)
{
   if (stack == NULL || stack->list == NULL) {
        return;  
    }
    
    // удаление первого элемента
    list_erase_first(stack->list);

}


bool stack_empty(const Stack *stack) {
    if (stack == NULL || stack->list == NULL) {
        return true;
    }
    
    return (list_first(stack->list) == NULL);
}
