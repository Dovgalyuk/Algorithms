
#include <iostream>
#include <stdexcept>
#include <string>
#include "../stack.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2)
        return 1;

    int test = stoi(argv[1]);
    Stack<int> stack;

    switch (test)
    {
    case 1:
        if (!stack.empty() || stack.size() != 0)
            return 1;
        break;

    case 2:
        stack.push(10);
        if (stack.size() != 1 || stack.top() != 10)
            return 1;
        break;

    case 3:
        stack.push(10);
        stack.push(20);
        if (stack.top() != 20)
            return 1;
        break;

    case 4:
        stack.push(10);
        stack.push(20);
        stack.pop();
        if (stack.top() != 10 || stack.size() != 1)
            return 1;
        break;

    case 5:
        stack.push(10);
        stack.pushBottom(20);
        if (stack.bottom() != 20 || stack.size() != 2)
            return 1;
        break;

    case 6:
        stack.push(10);
        stack.push(20);
        if (stack.bottom() != 10)
            return 1;
        break;

    case 7:
        stack.push(10);
        stack.push(20);
        stack.popBottom();
        if (stack.bottom() != 20 || stack.size() != 1)
            return 1;
        break;

    case 8:
        stack.push(10);
        stack.push(20);
        stack.push(30);
        stack.reverse();

        if (stack.at(0) != 10 ||
            stack.at(1) != 20 ||
            stack.at(2) != 30)
            return 1;
        break;

    case 9:
        stack.push(10);
        stack.push(20);
        stack.clear();
        if (!stack.empty() || stack.size() != 0)
            return 1;
        break;

    case 10:
        stack.push(10);
        stack.push(20);
        stack.push(30);
        if (stack.at(1) != 20)
            return 1;
        break;

    case 11:
        try
        {
            stack.pop();
            return 1;
        }
        catch (const runtime_error&)
        {
        }
        break;

    case 12:
        try
        {
            stack.at(0);
            return 1;
        }
        catch (const out_of_range&)
        {
        }
        break;

    default:
        return 1;
    }

    cout << "Stack test " << test << " passed" << endl;
    return 0;
}
