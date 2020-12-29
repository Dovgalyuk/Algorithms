#include <iostream>
#include <string>
#include "stack.h"
using namespace std;
 
bool CheckRightStr(string str, const string openDelim = "([{", const string closeDelim = ")]}")
{
    Stack* stack = new Stack();
    bool right = true;
    for (int i = 0; i < str.size(); i++)
    {
        auto index = openDelim.find(str[i]);
        if (index != string::npos)
        {
            stack->Push(str[i]);
        }
        else
        {
            if (!stack->Empty())
            {
                auto index = closeDelim.find(str[i]);
                if (stack->Get() != openDelim[index])
                {
                    right = false;
                    break;
                }
                else
                {
                    stack->Pop();
                }
            }
            else
            {
                right = false;
                break;
            }
        }
    }
 
    right = right && stack->Empty();
    delete stack;
    return right;
}
 
void Say(bool value)
{
    if (value) cout << "YES";
    else cout << "NO";
}
 
int main()
{
    string toCheck;
    cout << "Enter string to check: ";
    cin >> toCheck;
    Say(CheckRightStr(toCheck));
}