#include <stdlib.h>
#include "stack.h"
#include "list.h"

typedef struct Stack {
    List *list;
} Stack;

Stack *stack_create(FFree f)
{
    Stack *stack = malloc(sizeof(Stack));
    if (!stack) return NULL;
    stack->list = list_create(f);
    if (!stack->list) {
        free(stack);
        return NULL;
    }
    return stack;
}

void stack_delete(Stack *stack)
{
    if (!stack) return;
    list_delete(stack->list);
    free(stack);
}

void stack_push(Stack *stack, Data data)
{
    if (!stack) return;
    list_insert(stack->list, data);
}

/* проверка непустоты стека перед вызовом обязтельна.
у нас 0 может хранится как данные, потому надо
*/
Data stack_get(const Stack *stack)
{
    if (!stack) return (Data)0; // я бы не вставлял это вообще, но по шаблону выглядит что нужно так
    ListItem *data = list_first(stack->list);
    return list_item_data(data);
}

void stack_pop(Stack *stack)
{
    if (!stack) return;
    list_erase_first(stack->list);
}

bool stack_empty(const Stack *stack)
{
    if (!stack || !stack->list) return true;
    return list_first(stack->list) == NULL;
}
