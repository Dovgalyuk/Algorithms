#ifndef STACK_H
#define STACK_H

typedef int Data;

struct Stack;

Stack* stack_create();
void stack_delete(Stack* stack);
void stack_push(Stack* stack, Data data);
Data stack_pop(Stack* stack);  
Data stack_get(const Stack* stack);
bool stack_empty(const Stack* stack);

#endif