/*
Написать программу, проверяющую правильность расстановки двух видов кавычек (“ и ‘) и скобок () в строке. 
Программа должна выводить YES для правильной последовательности и NO для неправильной.

"ab(c 'de' f)gt" --> YES
"adjsk 'z' frr') --> NO

*/
#include "stack.h"

#include <iostream>
#include <string>

int main() {

    Stack* stack = stack_create();
    std::string str; 
    std::getline(std::cin, str);

    for (size_t i = 0; i < str.length(); i++)
    {
        char ch = str[i];
        if (ch == '\"' || ch == '\'' || ch == '(' || ch == ')') 
        {
            if ( (stack_get(stack) == ch && ch != '(' && ch != ')') 
              || (stack_get(stack) == '(' && ch == ')') ) 
            {
                stack_pop(stack);
            } else {
                stack_push(stack, ch);
            }
        }
    }
    std::cout << (stack_empty(stack)? "YES" : "NO");
    
    stack_delete(stack);

    return 0;
}
