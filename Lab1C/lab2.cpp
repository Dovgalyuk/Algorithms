//–еализовать в проекте Library двусв€зный список(модуль list) и стек на основе этого списка(модуль stack).
//–ешить задачу, использу€ реализованный стек.
//Ќаписать программу, провер€ющую правильность расстановки двух видов кавычек(У и С) и скобок() в строке.ѕрограмма должна выводить YES дл€ правильной последовательности и NO дл€ неправильной.

#include "list.h"
#inlcude "stack.h"
#include <iostream>
#include <cstdlib>

using namespace std;

bool checkBracketsAndQuotes(Stack* bracketsAndQuotes, const string& input) {
    int count = 0;
    for (char c : input) {
        if (c == '(' || c == '[' || c == '{') {
            stack_push(bracketsAndQuotes, c);
        }
        else if (c == ')' || c == ']' || c == '}') {
            if (stack_empty(bracketsAndQuotes)) {
                return false;
            }
            char top = stack_get(bracketsAndQuotes);
            if ((c == ')' && top == '(') || (c == ']' && top == '[') || (c == '}' && top == '{') || (c == top && (count % 2 != 0)) || (c == top && (count % 2 != 0))) {
                stack_pop(bracketsAndQuotes);
            }
            else {
                return false;
            }
        }
        else if (c == '\"' || c == '\'') {
            if (stack_empty(bracketsAndQuotes)) {
                stack_push(bracketsAndQuotes, c);
            }
            else if (stack_get(bracketsAndQuotes) == c) {
                stack_pop(bracketsAndQuotes);
            }
            else {
                stack_push(bracketsAndQuotes, c);
            }
        }
    }
    return stack_empty(bracketsAndQuotes);
}

int main() {
    setlocale(LC_ALL, "Ru");
    Stack* bracketsAndQuotes = stack_create();
    string input;
    cout << "¬ведите строку, содержащую скобки и кавычки: ";
    getline(cin, input);

    if (checkBracketsAndQuotes(bracketsAndQuotes, input)) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
    stack_delete(bracketsAndQuotes);
    return 0;
}
