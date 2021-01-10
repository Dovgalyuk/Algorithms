#include <iostream>
#include "stack.h"

int main()
{
    Stack<Data> *stack = new Stack<Data>();

    stack->push(1);
    stack->push(2);
    stack->push(3);

    if (stack->get() != 3)
        std::cout << "Invalid stack top after push\n";

    std::cout << "Get: " << stack->get() << "\n";
    stack->pop();

    if (stack->get() != 2)
        std::cout << "Invalid stack top after pop\n";

    std::cout << "Get: " << stack->get() << "\n";
    stack->pop();

    if (stack->get() != 1)
        std::cout << "Invalid stack top after pop\n";

    std::cout << "Get: " << stack->get() << "\n";
    stack->push(4);
    stack->push(5);

    if (stack->get() != 5)
        std::cout << "Invalid stack top after push\n";

    while (!stack->empty())
    {
        std::cout << "Get: " << stack->get() << "\n";
        stack->pop();
    }

    delete stack;
}
