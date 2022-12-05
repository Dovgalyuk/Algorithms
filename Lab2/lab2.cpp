#include <iostream>
#include <string>
#include "stack.h"

using namespace std;

int main()
{
    Stack* stack = stack_create();
    string a;
    int a1 = 0, a2 = 0, a3 = 0, a4 = 0;
    getline(cin, a);
    for(int i = 0; i < a.size(); i++)
    {
        stack_push(stack, a[i]);
    }
    while (stack_empty(stack))
    {
        switch (stack_get(stack)) {
        case '[':
            a1++;
                break;
        case '{':
            a2++;
                break;
        case '(':
            a3++;
            break;
        case '<':
            a4++;
            break;
        case ']':
            a1--;
            break;
        case '}':
            a2--;
            break;
        case ')':
            a3--;
            break;
        case '>':
            a4--;
            break;
        default:
            break;
        }
        stack_pop(stack);
    }
    if (a1 == 0 && a2 == 0 && a3 == 0 && a4 == 0)
        cout << "YES";
    else
        cout << "NO";
    stack_delete(stack);
}
