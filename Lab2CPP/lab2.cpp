    #include <iostream>
    #include <fstream>
    #include <string>
    #include "vector.h"
    #include "stack.h"

    Stack *stack_create_and_read(std::ifstream &input)
    {
        std::string line;
        std::getline(input, line);

        Stack* stack = stack_create();
        for(char c : line) {
            stack_push(stack, c);
        }
        return stack;
    }

    bool check(Stack* stack) {
        Stack* new_stack = stack_create();
        Stack* temp_stack = stack_create();
        while (!stack_empty(stack)) {
            char c = stack_get(stack);
            stack_pop(stack);
            stack_push(temp_stack, c);
        }
        bool flag = true;
        while (!stack_empty(temp_stack)) {
            char c = stack_get(temp_stack);
            stack_pop(temp_stack);
            stack_push(stack, c);
            if (c == '(') {
                stack_push(new_stack, '(');
            }
            else if (c == ')') {
                if (stack_empty(new_stack) || stack_get(new_stack) != '(') {
                    flag = false;
                } else {
                    stack_pop(new_stack);
                }
            }
            else if (c == '\"' || c == '\'') {
                if (!stack_empty(new_stack) && stack_get(new_stack) == c) {
                    stack_pop(new_stack);
                } else {
                    stack_push(new_stack, c);
                }
            }
        }
        
        if (flag && !stack_empty(new_stack)) {
            flag = false;
        }
        
        stack_delete(new_stack);
        stack_delete(temp_stack);
        return flag;
    }

    int main(int argc, char **argv)
    { 
        Stack* stack = NULL;
        std::ifstream input(argv[1]);
        stack = stack_create_and_read(input);
        if(check(stack)){
            std::cout << "YES";
        }
        else
        {
            std::cout << "NO";
        }
        stack_delete(stack);
        input.close();
        
    }