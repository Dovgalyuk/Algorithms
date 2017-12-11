#include <iostream>
#include "stack.h"

int main()
{


	
	Stack *stack = stack_create();
	


    stack_push(stack, 1);
    stack_push(stack, 2);
    stack_push(stack, 3);

    std::cout << "Get: " << stack_get(stack) << "\n";
    stack_pop(stack);
    std::cout << "Get: " << stack_get(stack) << "\n";
    stack_pop(stack);
    std::cout << "Get: " << stack_get(stack) << "\n";
    stack_push(stack, 4);
    stack_push(stack, 5);
    while (!stack_empty(stack))
    {
        std::cout << "Get: " << stack_get(stack) << "\n";
        stack_pop(stack);
    }

    stack_delete(stack);
	
	}

