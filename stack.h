#ifndef STACK_H
#define STACK_H

struct Stack;

// создание пустого стека
Stack *stack_create();

// удаление стека
void stack_delete(Stack *stack);

// включение элемента в стек
void stack_push(Stack *stack, int Data);

// получение последнего элемента стека
int stack_get(Stack *stack);

// выталкивание элемента из стека
void stack_pop(Stack *stack);

// проверка стека на наличие элементов
bool stack_empty(Stack *stack);

#endif
