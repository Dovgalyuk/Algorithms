#include <iostream>
#include <fstream>
#include <stdexcept>
#include "stack.h"  
#include "vector.h" 
#include <string>

int precedence(char op) {
    if (op == '+' || op == '-') return 1; 
    if (op == '*' || op == '/') return 2; 
    return 0;
}

int apply_operator(int a, int b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if (b == 0) throw std::runtime_error("Division by zero");
        return a / b;
    default:
        throw std::invalid_argument("Invalid operator");
    }


}

int evaluate_example(const std::string& example) { 
    Stack* values = stack_create();
    Stack* operators = stack_create();

    for (size_t i = 0; i < example.length(); i++) {

        if (example[i] == ' ') continue;

        if (isdigit(example[i])) {
            int value = 0;
            while (i < example.length() && isdigit(example[i])) {
                value = value * 10 + (example[i] - '0');
                i++;
            }
            i--;
            stack_push(values, value);
        }

        else if (example[i] == '(') {
            stack_push(operators, example[i]);
        }
       
        else if (example[i] == ')') {
            while (stack_get(operators) != '(') {
                if (stack_empty(values)) throw std::runtime_error("Invalid expression");
                int val2 = stack_get(values);
                stack_pop(values);
                if (stack_empty(values)) throw std::runtime_error("Invalid expression");
                int val1 = stack_get(values);
                stack_pop(values);
                
                char op = (char)stack_get(operators);
                stack_pop(operators);
                stack_push(values, apply_operator(val1, val2, op));
            }
           
            if (!stack_empty(operators)) {
                stack_pop(operators);
            }

        }
        
        else if (example[i] == '+' || example[i] == '-' || example[i] == '*' || example[i] == '/') {
            while (!stack_empty(operators)&&precedence((char)stack_get(operators)) >= precedence(example[i])) {
                if (stack_empty(values)) throw std::runtime_error("Invalid expression");
                int val2 = stack_get(values);
                stack_pop(values);
                if (stack_empty(values)) throw std::runtime_error("Invalid expression");
                int val1 = stack_get(values);
                stack_pop(values);
               
                char op = (char)stack_get(operators);
                stack_pop(operators);
                stack_push(values, apply_operator(val1, val2, op));
            }
            stack_push(operators, example[i]);
        }
    }

    
    while (!stack_empty(operators)) {
        if (stack_empty(values)) throw std::runtime_error("Invalid expression");
        int val2 = stack_get(values);
        stack_pop(values);

        if (stack_empty(values)) throw std::runtime_error("Invalid expression");
        int val1 = stack_get(values);
        stack_pop(values);

        
        char op = (char)stack_get(operators);
        stack_pop(operators);

        stack_push(values, apply_operator(val1, val2, op));
    }
    if (stack_empty(values)) {
       
        return 0;
        
    }
    else {
        int result = stack_get(values);
        stack_delete(values);
        stack_delete(operators);
        return result;
    }
}

int main() {
    std::ifstream inputFile("input.txt");
    std::string example;

    if (inputFile.is_open()) {
        
     std::getline(inputFile, example);
       
    }
    inputFile.close();
    int result = evaluate_example(example);
    std::cout << "result: " << result << std::endl;


    return 0;
}