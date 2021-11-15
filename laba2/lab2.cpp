#include<iostream>
#include<stack.h>
using namespace std;
int main()
{
    Stack<char> *stack = new Stack<char>();
    std::string str = R"(n‘z’n)";
    for (char i: str) {
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
    return 0;
}


