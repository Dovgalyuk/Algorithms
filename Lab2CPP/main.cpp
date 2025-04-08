#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

using namespace std;

string check_balance(const string& b) {
    Stack* stack = stack_create();
    int a = b.length();
    
    for (int i = 0; i < a; ++i) {
        if (stack_empty(stack)) stack_push(stack, b[i]);
        else if (b[i] == ']') {
            if (stack_get(stack) == '[') stack_pop(stack);
            else stack_push(stack, b[i]);
        }
        else if (b[i] == ')') {
            if (stack_get(stack) == '(') stack_pop(stack);
            else stack_push(stack, b[i]);
        }
        else if (b[i] == '}') {
            if (stack_get(stack) == '{') stack_pop(stack);
            else stack_push(stack, b[i]);
        }
        else if (b[i] == '\'') {
            if (stack_get(stack) == '\'') stack_pop(stack);
            else stack_push(stack, b[i]);
        }
        else if (b[i] == '"') {
            if (stack_get(stack) == '"') stack_pop(stack);
            else stack_push(stack, b[i]);
        }
        else stack_push(stack, b[i]);
    } 
    
    string result = stack_empty(stack) ? "YES" : "NO";
    stack_delete(stack);
    return result;
}

int main(int argc, char *argv[]) {
    string input;

    if (argc > 1) {
        ifstream input_file(argv[1]);
        if (input_file.is_open()) {
            getline(input_file, input);
            input_file.close();
        } else {
            cerr << "Не удалось открыть файл " << argv[1] << ". Введите данные вручную:\n";
            getline(cin, input);
        }
    } else {
        cerr << "Файл не передан. Введите данные вручную:\n";
        getline(cin, input);
    }

    cout << check_balance(input) << endl;

    return 0;
}
