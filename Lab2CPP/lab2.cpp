#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "stack.h"

using namespace std;

void machine_operations(const string& filename){
    Stack *stack = stack_create();

    vector<int> storing_iload(4, 0);

    ifstream file(filename);
    string str;

    while (getline(file, str)){
        istringstream commands(str);
        string operation;
        commands >> operation;

        if (operation == "bipush"){
            int number;
            commands >> number;
            stack_push(stack, number);
        }
        else if (operation == "pop"){
            if (!stack_empty(stack)) {
                stack_pop(stack);
            } else {
                cerr << "error: stack is empty" << endl;
            }
        }
        else if (operation == "imul"){
            int a = stack_get(stack);
            stack_pop(stack);
            int b = stack_get(stack);
            stack_pop(stack);
            stack_push(stack, a * b);
        }
        else if (operation == "iand"){
            int a = stack_get(stack);
            stack_pop(stack);
            int b = stack_get(stack);
            stack_pop(stack);
            stack_push(stack, a & b);
        }
        else if (operation == "ior"){
            int a = stack_get(stack);
            stack_pop(stack);
            int b = stack_get(stack);
            stack_pop(stack);
            stack_push(stack, a | b);
        }
        else if (operation == "ixor"){
            int a = stack_get(stack);
            stack_pop(stack);
            int b = stack_get(stack);
            stack_pop(stack);
            stack_push(stack, a ^ b);
        }
        else if (operation == "iadd"){
            int a = stack_get(stack);
            stack_pop(stack);
            int b = stack_get(stack);
            stack_pop(stack);
            stack_push(stack, a + b);
        }
        else if (operation == "isub"){
            int a = stack_get(stack);
            stack_pop(stack);
            int b = stack_get(stack);
            stack_pop(stack);
            stack_push(stack, b - a);
        }
        else if (operation == "iload_0"){
            stack_push(stack, storing_iload[0]);
        }
        else if (operation == "iload_1") { 
            stack_push(stack, storing_iload[1]);
        }
        else if (operation == "iload_2") { 
            stack_push(stack, storing_iload[2]);
        }
        else if (operation == "iload_3") { 
            stack_push(stack, storing_iload[3]);
        }
        else if (operation == "istore_0") {
            storing_iload[0] = stack_get(stack);
            stack_pop(stack);
        }
        else if (operation == "istore_1") { 
            storing_iload[1] = stack_get(stack);
            stack_pop(stack);
        }
        else if (operation == "istore_2") { 
            storing_iload[2] = stack_get(stack);
            stack_pop(stack);
        }
        else if (operation == "istore_3"){ 
            storing_iload[3] = stack_get(stack);
            stack_pop(stack);
        }
        else if (operation == "swap") {
            int a = stack_get(stack);
            stack_pop(stack);
            int b = stack_get(stack);
            stack_pop(stack);
            stack_push(stack, a);
            stack_push(stack, b);
        }
    }

    cout << "stack:" << endl;
    while (!stack_empty(stack)) {
        cout << stack_get(stack) << endl;
        stack_pop(stack);
    }

    cout << "vars:" << endl;
    for (size_t i = 0; i < storing_iload.size(); i++) {
        cout << storing_iload[i] << endl;
    }

    stack_delete(stack);
    file.close();
}

int main(int argc, char* argv[]){
    if (argc != 2) {
        cerr << "usage: " << argv[0] << " <file_path>" << endl;
        return 1;
    }

    string filename = argv[1];
    machine_operations(filename);
    
    return 0;
}