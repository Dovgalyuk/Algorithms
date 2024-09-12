#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

// Function to return the precedence of an operator
int precedence(char op) {
    if (op == '+') {
        return 1; // Precedence for addition
    }
    if (op == '*') {
        return 2; // Precedence for multiplication
    }
    return 0;
}

// Function to perform operation using custom Stack
void performOperation(Stack &values, int op, std::ofstream &output) {
    int val1 = values.get(); // Get top value (equivalent to "POP A")
    values.pop();            // Remove top value from stack
    int val2 = values.get();  // Get the second top value (equivalent to "POP B")
    values.pop();             // Remove the second top value from stack

    output << "POP A" << std::endl;
    output << "POP B" << std::endl;

    if (op == 1) { // '+' operation
        output << "ADD A, B" << std::endl;
        values.push(val1 + val2); // Push result onto the stack
    } else if (op == 2) { // '*' operation
        output << "MUL A, B" << std::endl;
        values.push(val1 * val2); // Push result onto the stack
    }

    output << "PUSH A" << std::endl;
}

// Main function to translate expression into assembly-like stack operations
void translateToAssembly(const std::string &expr, std::ofstream &output) {
    Stack values; // Custom Stack for values
    Stack ops;    // Custom Stack for operators

    for (size_t i = 0; i < expr.size(); ++i) {
        char token = expr[i];

        // If token is a space, skip it
        if (token == ' ') {
            continue;
        }

        // Handle multi-digit numbers
        if (isdigit(token)) {
            int value = 0;
            // Collect the full number
            while (i < expr.size() && isdigit(expr[i])) {
                value = value * 10 + (expr[i] - '0');
                ++i;
            }
            --i; // Move back one character

            output << "PUSH " << value << std::endl;
            values.push(value); // Push the number onto the stack
        }

        // Handle opening parenthesis
        else if (token == '(') {
            ops.push(0); // Use '0' to represent '(' in the operators stack
        }

        // Handle closing parenthesis
        else if (token == ')') {
            // Process until we encounter '('
            while (!ops.empty() && ops.get() != 0) {
                performOperation(values, ops.get(), output);
                ops.pop();
            }
            ops.pop(); // Remove the '(' from the operators stack
        }

        // Handle operators '+' and '*'
        else if (token == '+' || token == '*') {
            // Perform operations with higher or equal precedence
            while (!ops.empty() && precedence(ops.get()) >= precedence(token)) {
                performOperation(values, ops.get(), output);
                ops.pop();
            }
            ops.push(precedence(token)); // Push the current operator onto the stack
        }
    }

    // Complete remaining operations in the stack
    while (!ops.empty()) {
        performOperation(values, ops.get(), output);
        ops.pop();
    }
}

int main(int argc, char **argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

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

    while (t-- > 0) {
        std::string s;
        input >> s;
        translateToAssembly(s, output); // Process each expression and write to output file
    }

    input.close();
    output.close();

    return 0;
}
