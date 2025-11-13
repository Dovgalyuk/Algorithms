    #include <iostream>
    #include <fstream>
    #include <string>
    #include "vector.h"
    #include "stack.h"

    bool check(const std::string& line)
    {
        Stack* stack = stack_create();
        
        for (char c : line) {
            if (c == '(') {
                stack_push(stack, 'R');
            }
            else if (c == ')') {
                if (stack_empty(stack) || stack_get(stack) != 'R') {
                    stack_delete(stack);
                    return false;
                }
                stack_pop(stack);
            }
            else if (c == '\"') {
                if (!stack_empty(stack) && stack_get(stack) == 'D') {
                    stack_pop(stack);
                } else {
                    stack_push(stack, 'D');
                }
            }
            else if (c == '\'') {
                if (!stack_empty(stack) && stack_get(stack) == 'S') {
                    stack_pop(stack);
                } else {
                    stack_push(stack, 'S');
                }
            }
        }
        bool result = stack_empty(stack);
        stack_delete(stack);
        return result;
    }

    int main(int argc, char **argv)
    { 
        std::ifstream input(argv[1]);
        std::string line;
        std::getline(input, line);
        if(check(line)){
            std::cout << "YES";
        }
        else
        {
            std::cout << "NO";
        }
        input.close();
    }