#include <iostream>
#include "list.h"
#include "stack.h"
#include <string>

using namespace std;



void deistvie(Stack* stack, string command, int o)
{
    string l;

    if (command.length() == 6)
    {
        o = (int)command[5] - (int)'0';
        if (o > 3)
            cout << "BAD PUSH" << endl;
        else 
        {
            cout << "Push " << o << endl;
            stack_push(stack, o);
        }
    }
    else
    {
        if(stack_empty(stack) == true)
                cout << "BAD POP" << endl;
        else
        {
            cout << stack_get(stack) << endl;
            stack_pop(stack);
        }
    }
}
int main() {
    Stack* stack = stack_create();
    string command, command1, command2, command3, command4, command5;
    int size;
    cin >> size;
    cout << endl;
    int o = 0;
    getline(cin, command1);
    getline(cin, command2);
    getline(cin, command3);
    getline(cin, command4);
    getline(cin, command5);
    deistvie(stack, command1, o);
    deistvie(stack, command2, o);
    deistvie(stack, command3, o);
    deistvie(stack, command4, o);
    deistvie(stack, command5, o);

    return 0;

}
