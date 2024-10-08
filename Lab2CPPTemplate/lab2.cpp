#include <stdio.h>
#include <stdexcept>
#include <string>
#include "stack.h"

using namespace std;

string polish_notation(string& expression);
int precedence(char op);
bool isLatinLetter(char c);

int main(int argc, char** argv)
{
    char In[100];
    FILE* input = fopen(argv[1], "r");
    if (fscanf(input, "%s", &In) == 0)
        throw invalid_argument("Failed to read the input file");

    string line(In); // construct a std::string from the input
    string out = polish_notation(line);

    printf("%s", out.c_str());
    
    return 0;
}

string polish_notation(string &expression)
{
    Stack<int> operator_stack;
    string rpn_expression;

    for (char ch : expression) {
        // single-letter variable check
        if (isLatinLetter(ch)) {
            rpn_expression += ch;
        }
        // handle operators (+, -, *, /)
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            if (operator_stack.empty() || precedence(ch) > precedence(operator_stack.get())) {
                operator_stack.push(ch);
            }
            else {
                while (!operator_stack.empty() && precedence(ch) <= precedence(operator_stack.get())) {
                    rpn_expression += operator_stack.get();
                    operator_stack.pop();
                }

                operator_stack.push(ch);
            }
        }
        // handle left parentheses
        else if (ch == '(') {
            operator_stack.push(ch);
        }
        // handle right parentheses
        else if (ch == ')') {
            while (operator_stack.get() != '(') {
                rpn_expression += operator_stack.get();
                operator_stack.pop();
            }
            operator_stack.pop(); // Remove the left parenthesis
        }
        // handle non-convertable expression
        else {
            throw invalid_argument("Unable to convert.");
        }
    }

    // Having finished reading the characters of string, we rewrite the elements from the stack to out string.
    while (!operator_stack.empty()) {
        rpn_expression += operator_stack.get();
        operator_stack.pop();
    }

    return rpn_expression;
}

// Helper function to determine operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    else {
        return 0;
    }
}

// Function of checking for one-letter variable
bool isLatinLetter(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}
