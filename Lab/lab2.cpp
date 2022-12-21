#include <iostream>
#include "list.h"
#include "stack.h"
#include <string>

using namespace std;



void deistvie(Stack* stack, int size, string command)
{
    string l;
    int o = 0;

    if (command.length() == 6)
    {
        o = (int)command[5] - (int)'0';
        if (o > size)
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
            cout << o << endl;
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
    getline(cin, command1);
    getline(cin, command2);
    getline(cin, command3);
    getline(cin, command4);
    getline(cin, command5);
    deistvie(stack, size, command1);
    deistvie(stack, size, command2);
    deistvie(stack, size, command3);
    deistvie(stack, size, command4);
    deistvie(stack, size, command5);

    return 0;

}
