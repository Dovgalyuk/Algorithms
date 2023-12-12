/*
Написать программу, проверяющую правильность расстановки двух видов кавычек (“ и ‘) и скобок () в строке. 
Программа должна выводить YES для правильной последовательности и NO для неправильной.

"ab(c 'de' f)gt" --> YES
"adjsk 'z' frr') --> NO

*/
#include "stack.h"

#include <ctime>
#include <iostream>
#include <string>

int main() {

    Stack* stack = stack_create();
    std::string str; 
    std::getline(std::cin, str);

    for (size_t i = 0; i < str.length(); i++)
    {
        if (str[i] == '\"' || str[i] == '\'' || str[i] == '(' || str[i] == ')') {
            char ch = str[i];
            if (str[i] == ')') {
                ch = '(';
            }
            if (stack_get(stack) == ch) {
                stack_pop(stack);
            }
            else {
                stack_push(stack, ch);
            }
        }
    }
    if (stack_empty(stack)) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }

    stack_delete(stack);

    return 0;
}
