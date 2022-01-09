#include <iostream>
#include <string>
#include <stack.h>

std::string writeString()
{
    std::string strokavvoda;
    std::cout << "Vvodtext: " << std::endl;
    std::getline(std::cin, strokavvoda);
    return strokavvoda;

}

void fillStack(Stack<char>& oneStack, std::string strokavvoda)
{
    for (auto symbol : strokavvoda)
    {
        if (symbol == '#')
        {
            oneStack.pop();
        }
        else
        {
            oneStack.push(symbol);
        }
    }
}

int main()
{
    std::string strokavvoda = writeString();
    std::cout << strokavvoda << std::endl;
    Stack<char> oneStack;
    fillStack(oneStack, strokavvoda);
    std::string exitString;
    while (!oneStack.empty())
    {
        exitString = oneStack.get() + exitString;
        oneStack.pop();
    }
    std::cout << exitString << std::endl;
    return 0;
}