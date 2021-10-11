#include <iostream>
#include <string>
#include <stack.h>

std::string writeString()
{
    std::string inputString;
    std::cout << "input text: " << std::endl;
    std::getline(std::cin, inputString);
    return inputString;
    
}

void fillStack(Stack<char> &myStack, std::string inputString)
{
    for (auto symbol : inputString)
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
    std::string inputString = writeString();
    std::cout << inputString << std::endl;
    Stack<char> myStack;
    fillStack(myStack, inputString);
    std::string outputString;
    while (!myStack.empty())
    {
        outputString = myStack.get() + outputString;
        myStack.pop();
    }
    std::cout << outputString << std::endl;
    return 0;
}
