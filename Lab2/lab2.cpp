#include <iostream>
#include <string>
#include "stack.h"
#include "list.h"

using namespace std;


int main()
{
    Stack* stack_special = stack_create();
    string a;
    char o;
    bool prav = true;
    getline(cin, a);
    for (int i = 0; i < a.size(); i++)
    {
        o = a[i];
        if (o == '(' || o == '{' || o == '[' || o == '<')
        {
            stack_push(stack_special, o);
        }
        else
        {
            if ((stack_get(stack_special) == int(o) - 2) || (stack_get(stack_special) == '(' && o == ')'))
            {
                stack_pop(stack_special);
            }
            else
            {
                prav = false;
                break;
            }
        }
    }
    if (prav)
        cout << "YES";
    else
        cout << "NO";
    stack_delete(stack_special);
}
