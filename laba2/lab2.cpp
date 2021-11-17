#include<iostream>
#include<stack.h>
#include<string>

int main()
{
    Stack<char> *stack = new Stack<char>();
    std::cout <<"Enter the line:";
    std::string str;
    getline(std::cin,str);
    std::cout << std::endl;
    for (char i: str)
    {
        if (!stack->empty() && stack->get() == '(' && i == ')') {
            stack->pop();
        }
        else if (!stack->empty() && stack->get() == '{' && i == '}') {
            stack->pop();
        }
        else if (!stack->empty() && stack->get() == '[' && i == ']') {
            stack->pop();
        }
        else if (!stack->empty() && stack->get() == '\'' && i == '\'') {
            stack->pop();
        }
        else if (!stack->empty() && stack->get() == '"' && i == '"') {
            stack->pop();
        }
        else if (i == '\'' || i == '"' || i == '(' || i == '{' || i == '[' || i == ')' || i == '}' || i == ']') {
            stack->push(i);
        }
    }
    if (stack->empty()) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }
    delete stack;
    return 0;
}


