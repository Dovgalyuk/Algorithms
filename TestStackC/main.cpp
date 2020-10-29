#include <iostream>
#include "../LibraryCPP/stack.h"

int main()
{
    Stack *stack = new Stack();

    stack->Push(1);
    stack->Push(2);
    stack->Push(3);

    if (stack->Get() != 3)
        std::cout << "Invalid stack top after push\n";

    std::cout << "Get: " << stack->Get() << "\n";
    stack->Pop();

    if (stack->Get() != 2)
        std::cout << "Invalid stack top after pop\n";

    std::cout << "Get: " << stack->Get() << "\n";
    stack->Pop();

    if (stack->Get() != 1)
        std::cout << "Invalid stack top after pop\n";

    std::cout << "Get: " << stack->Get() << "\n";
    stack->Push(4);
    stack->Push(5);

    if (stack->Get() != 5)
        std::cout << "Invalid stack top after push\n";

    while (!stack->Empty())
    {
        std::cout << "Get: " << stack->Get() << "\n";
        stack->Pop();
    }

    delete stack;
}
