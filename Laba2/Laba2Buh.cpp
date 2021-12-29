#include <cstddef>
#include <string>
#include <iostream>
#include <string>
#include "list.cpp"
#include "stack.cpp"

using namespace std;
typedef char Data;

int main()
{
    Stack* steck;
    int zakskob = 0, zakodin = 0, zakdwa = 0;
    steck = stack_create();
    char elem = '1';
    while (elem != '\n')
    {
        elem = getchar();
        stack_push(steck, elem);
    }
    while (!stack_empty(steck))
    {
        char elem;
        elem = stack_get(steck);
        if (elem == (char)40 && zakskob == 1)
        {
            zakskob = 0;
        }
        else if (elem == (char)39 && zakodin == 1)
        {
            zakodin = 0;
        }
        else if (elem == (char)34 && zakdwa == 1)
        {
            zakdwa = 0;
        }
        else if (elem == (char)41)
        {
            zakskob = 1;
        }
        else if (elem == (char)39)
        {
            zakodin = 1;
        }
        else if (elem == (char)34)
        {
            zakdwa = 1;
        }
        stack_pop(steck);
    }
    if (zakskob == 0 && zakodin == 0 && zakdwa == 0)
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
    stack_delete(steck);
}