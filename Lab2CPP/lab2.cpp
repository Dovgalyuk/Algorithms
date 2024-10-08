#include <iostream>
#include "stack.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


using namespace std;

struct Variables
{
    int i0;
    int i1;
    int i2;
    int i3;
};


void performOperation(Variables* variables, Stack* stack, const vector<string>& operationItems)
{
    const string& operation = operationItems[0];


    if(operation == "bipush")
    {
        int value = stoi(operationItems[1]);
        stack_push(stack, value);
    }else if(operation == "pop")
    {
        stack_pop(stack);

    }else if(operation == "imul")
    {
        const int firstItem = stack_get(stack);
        stack_pop(stack);
        const int secondItem = stack_get(stack);
        stack_pop(stack);
        const int result = firstItem * secondItem;
        stack_push(stack, result);

    }else if(operation == "iand")
    {
        const int firstItem = stack_get(stack);
        stack_pop(stack);
        const int secondItem = stack_get(stack);
        stack_pop(stack);
        const int result = firstItem & secondItem;
        stack_push(stack, result);
    }else if(operation == "ior")
    {
        const int firstItem = stack_get(stack);
        stack_pop(stack);
        const int secondItem = stack_get(stack);
        stack_pop(stack);
        const int result = firstItem | secondItem;
        stack_push(stack, result);
    }else if(operation == "ixor")
    {
        const int firstItem = stack_get(stack);
        stack_pop(stack);
        const int secondItem = stack_get(stack);
        stack_pop(stack);
        const int result = firstItem ^ secondItem;
        stack_push(stack, result);
    }else if(operation == "iadd")
    {
        const int firstItem = stack_get(stack);
        stack_pop(stack);
        const int secondItem = stack_get(stack);
        stack_pop(stack);
        const int result = firstItem + secondItem;
        stack_push(stack, result);
    }else if(operation == "isub"){
        const int firstItem = stack_get(stack);
        stack_pop(stack);
        const int secondItem = stack_get(stack);
        stack_pop(stack);
        const int result = firstItem - secondItem;
        stack_push(stack, result);
    }
    else if(operation == "iload_0")
    {
        stack_push(stack, variables->i0);
    }else if(operation == "iload_1")
    {
        stack_push(stack, variables->i1);
    }else if(operation == "iload_2")
    {
        stack_push(stack, variables->i2);
    }else if(operation == "iload_3")
    {
        stack_push(stack, variables->i3);
    }else if(operation == "istore_0")
    {
        int data = stack_get(stack);
        variables->i0 = data;
        stack_pop(stack);
    }else if(operation == "istore_1")
    {
        int data = stack_get(stack);
        variables->i1 = data;
        stack_pop(stack);
    }else if(operation == "istore_2")
    {
        int data = stack_get(stack);
        variables->i2 = data;
        stack_pop(stack);
    }else if(operation == "istore_3")
    {
        int data = stack_get(stack);
        variables->i3 = data;
        stack_pop(stack);
    }else if(operation == "swap")
    {
        const int firstItem = stack_get(stack);
        stack_pop(stack);
        const int secondItem = stack_get(stack);
        stack_pop(stack);
        stack_push(stack, secondItem);
        stack_push(stack, firstItem);
    }

};

void printStack(Stack* stack)
{
    cout << "stack:" << endl;
    while (!stack_empty(stack))
    {
        int item = stack_get(stack);
        cout << item << endl;
        stack_pop(stack);
    }
}

void printVariables(Variables variables)
{
    cout << "vars:" << endl;
    cout << variables.i0 << endl;
    cout << variables.i1 << endl;
    cout << variables.i2 << endl;
    cout << variables.i3 << endl;
}

int main(int argc, char **argv) {

    std::ifstream file(argv[1]);

    Variables variables = Variables();
    variables.i0 = 0;
    variables.i1 = 0;
    variables.i2 = 0;
    variables.i3 = 0;

    Stack* stack = stack_create();


    std::string line;
    while (std::getline(file, line)) {
        vector<std::string> items;
        std::stringstream ss(line);
        std::string item;
        while (std::getline(ss, item, ' ')) {
            items.push_back(item);
        }
        performOperation(&variables, stack, items);
    }

    printStack(stack);
    printVariables(variables);

    stack_delete(stack);
    file.close();

    return 0;
}

