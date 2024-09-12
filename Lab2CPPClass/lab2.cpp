#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

// Function to return the precedence of an operator
int precedence(char op) {
    if (op == '+') {
        return 1;
    }
    if (op == '*') {
        return 2;
    }
    return 0;
}

void performOperation(Stack &values, int op, std::ofstream &output) {
    int val1 = values.get();
    values.pop();            
    int val2 = values.get();  
    values.pop();             

    output << "POP A" << std::endl;
    output << "POP B" << std::endl;

    if (op == 1) { // '+' operation
        output << "ADD A, B" << std::endl;
        values.push(val1 + val2);
    } else if (op == 2) { // '*' operation
        output << "MUL A, B" << std::endl;
        values.push(val1 * val2);
    }

    output << "PUSH A" << std::endl;
}

// Main function 
void translateToAssembly(const std::string &expr, std::ofstream &output) {
    Stack values;
    Stack ops;
    /* 
    I'm using:
    0 - '('
    1 - '+'
    2 - '*'
    */

    for (size_t i = 0; i < expr.size(); ++i) {
        char token = expr[i];

        if (token == ' ') {
            continue;
        }

        // Multi-digit numbers
        if (isdigit(token)) {
            int value = 0;
            while (i < expr.size() && isdigit(expr[i])) {
                value = value * 10 + (expr[i] - '0');
                ++i;
            }
            --i;

            output << "PUSH " << value << std::endl;
            values.push(value);
        } 
        else if (token == '(') {
            ops.push(0); // 0 - '('
        } 
        else if (token == ')') {
            // Searching '(' on stack
            while (ops.get() != 0) // 0 - '('
            {
                performOperation(values, ops.get(), output);
                ops.pop();
            }
            ops.pop();
        } 
        else if (token == '+' || token == '*') {

            while (!ops.empty() 
                    && precedence(ops.get()) >= precedence(token)) {
                performOperation(values, ops.get(), output);
                ops.pop();
            }
            ops.push(precedence(token));
        }
    }

    // Last Operating in stack
    while (!ops.empty()) {
        performOperation(values, ops.get(), output);
        ops.pop();
    }
}

int main(int argc, char **argv) {
    
    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Failed to open input file: " << argv[1] << "\n";
        return 1;
    }

    std::ofstream output(argv[2]);
    if (!output.is_open()) {
        std::cerr << "Failed to open output file: " << argv[2] << "\n";
        return 1;
    }

    size_t t;
    input >> t;

    while (t --> 0) // t-- > 0 cool vector)
    {
        std::string s;
        input >> s;
        translateToAssembly(s, output); 
    }

    input.close();
    output.close();

    return 0;
}
