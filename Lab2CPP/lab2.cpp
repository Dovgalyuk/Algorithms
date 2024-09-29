#include <iostream>
#include "stack.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>



using namespace std;

void performOperation(int& i0, int& i1, int& i2, int& i3, Stack* stack, const vector<string> operationItems)
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
        stack_push(stack, i0);
    }else if(operation == "iload_1")
    {
        stack_push(stack, i1);
    }else if(operation == "iload_2")
    {
        stack_push(stack, i2);
    }else if(operation == "iload_3")
    {
        stack_push(stack, i3);
    }else if(operation == "istore_0")
    {
        int data = stack_get(stack);
        i0 = data;
        stack_pop(stack);
    }else if(operation == "istore_1")
    {
        int data = stack_get(stack);
        i1 = data;
        stack_pop(stack);
    }else if(operation == "istore_2")
    {
        int data = stack_get(stack);
        i2 = data;
        stack_pop(stack);
    }else if(operation == "istore_3")
    {
        int data = stack_get(stack);
        i3 = data;
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

void printVariables(int i0, int i1, int i2, int i3)
{
    cout << "vars:" << endl;
    cout << i0 << endl;
    cout << i1 << endl;
    cout << i2 << endl;
    cout << i3 << endl;
}

int main(int argc, char **argv) {

    std::ifstream file(argv[1]);

    int i0 = 0;
    int i2 = 0;
    int i3 = 0;
    int i4 = 0;

    Stack* stack = stack_create();


    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> items;
        std::stringstream ss(line);
        std::string item;
        while (std::getline(ss, item, ' ')) {
            items.push_back(item);
        }
        performOperation(i0, i2, i3, i4, stack, items);
    }

    printStack(stack);
    printVariables(i0, i2, i3, i4);

    stack_delete(stack);
    file.close();

    return 0;
}

