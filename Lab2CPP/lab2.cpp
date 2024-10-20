#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

bool sequence(const std::string& sequence) {
    Stack* stack = stack_create();

    for (char c : sequence) {
        if (c == '(' || c == '[' || c == '{') {
            stack_push(stack, static_cast<Data>(c)); 
        }
        else if (c == ')' || c == ']' || c == '}') {
            if (stack_empty(stack)) {
                stack_delete(stack);
                return false; 
            }
            Data top = stack_get(stack); 
            stack_pop(stack); 
            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{')) {
                stack_delete(stack);
                return false; 
            }
        }
    }

    bool result = stack_empty(stack);
    stack_delete(stack); 
    return result;
}

int main() {
    std::ifstream infile("input.txt");
    std::ofstream outfile("output.txt"); 
    std::string s;

    std::getline(infile, s);
    if (sequence(s)) {
        outfile << "YES" << std::endl; 
    }
    else {
        outfile << "NO" << std::endl; 
    }

    return 0;
}
