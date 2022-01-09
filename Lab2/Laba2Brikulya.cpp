#include <iostream>
#include <string>
#include <stack.h>

std::string writeString()
{
    std::string VvodString;
    std::cout << "input text: " << std::endl;
    std::getline(std::cin, VvodString);
    return VvodString;
}

void fillStack(Stack<char>& myStack, std::string VvodString)
{
    for (auto symbol : VvodString)
    {
        if (symbol == '#')
        {
            myStack.pop();
        }
        else
        {
            myStack.push(symbol);
        }
    }
}

int main()
{
    std::string VvodString = writeString();
    std::cout << VvodString << std::endl;
    Stack<char> myStack;
    fillStack(myStack, VvodString);
    std::string exitString;
    while (!myStack.empty())
    {
        exitString = myStack.get() + exitString;
        myStack.pop();
    }
    std::cout << exitString << std::endl;
    return 0;
}