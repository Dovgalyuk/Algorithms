#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

static int tp = 0;
static int tf = 0;

void assert(bool expr, char* msg){
    if (expr) tp++;
    else tf++;
    printf(msg);
    printf("\n");
}


int main() {
    Stack *stack = stack_create(NULL);
    assert(stack != NULL, "stack not null");
    assert(stack_empty(stack) == true, "new stack is empty");
    stack_delete(stack);
    
    stack = stack_create(NULL);
    stack_push(stack, (Data)10);
    assert(stack_empty(stack) == false, "stack not empty");
    assert(stack_get(stack) == 10, "stack_get return 10");
    stack_delete(stack);
    
    stack = stack_create(NULL);
    stack_push(stack, (Data)10);
    stack_push(stack, (Data)20);
    stack_push(stack, (Data)30);
    assert(stack_get(stack) == 30, "30 on top");
    stack_pop(stack);
    assert(stack_get(stack) == 20, "20 on top");
    stack_pop(stack);
    assert(stack_get(stack) == 10, "10 on top");
    stack_pop(stack);
    assert(stack_empty(stack) == true, "stack empty");
    stack_delete(stack);
    
    assert(stack_empty(NULL) == true, "stack_empty(NULL) safe");
    assert(stack_get(NULL) == (Data)0, "stack_get(NULL) safe");
    stack_push(NULL, (Data)10);
    stack_pop(NULL);
    stack_delete(NULL);
    
    stack = stack_create(NULL);
    stack_push(stack, (Data)0);
    assert(stack_empty(stack) == false, "0 on top stack dont empty");
    assert(stack_get(stack) == 0, "stack_get return 0");
    stack_delete(stack);
    
    printf("\nResults: %d passed, %d failed\n", tp, tf);
    return tf > 0 ? 1 : 0;
}