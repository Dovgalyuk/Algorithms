//Реализовать в проекте Library двусвязный список(модуль list) и стек на основе этого списка(модуль stack).
//Решить задачу, используя реализованный стек.
//Написать программу, проверяющую правильность расстановки двух видов кавычек(“ и ‘) и скобок() в строке.Программа должна выводить YES для правильной последовательности и NO для неправильной.

#include "list.h"
#inlcude "stack.h"
#include <iostream>
#include <cstdlib>

using namespace std;

bool checkBracketsAndQuotes(Stack* bracketsAndQuotes, const string& input) {

    for (char c : input) {
        if (c == '(' || c == '[' || c == '{' || c == '"' || c == '\'') {
            stack_push(bracketsAndQuotes, c);
        }
        else if (c == ')' || c == ']' || c == '}' || c == '"' || c == '\'') {
            if (stack_empty(bracketsAndQuotes)) {
                return false;
            }
            char top = stack_get(bracketsAndQuotes);
            if ((c == ')' && top == '(') || (c == ']' && top == '[') || (c == '}' && top == '{') || (c == '"' && top == '"') || (c == '\'' && top == '\'')) {
                stack_pop(bracketsAndQuotes);
            }
            else {
                return false;
            }
        }
    }

    return stack_empty(bracketsAndQuotes);
}

int main() {
    setlocale(LC_ALL, "Ru");
    Stack* bracketsAndQuotes = stack_create();
    string input;
    cout << "Введите строку, содержащую скобки и кавычки: ";
    getline(cin, input);

    if (checkBracketsAndQuotes(bracketsAndQuotes, input)) {
        cout << "YES: Правильная последовательность скобок и кавычек" << endl;
    }
    else {
        cout << "NO: Неправильная последовательность скобок и кавычек" << endl;
    }
    stack_delete(bracketsAndQuotes);
    return 0;
}
