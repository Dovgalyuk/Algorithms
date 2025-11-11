#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <fstream>
#include "stack.h"

using namespace std;

class Calculator {
private:
    static int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

    static int apply_operation(int a, int b, char op) {
        switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw runtime_error("Division by zero");
            return a / b;
        }
        return 0;
    }

    static void process_operator(Stack* values, Stack* operators) {
        if (stack_empty(values)) throw runtime_error("Invalid expression");
        int b = stack_get(values); stack_pop(values);

        if (stack_empty(values)) throw runtime_error("Invalid expression");
        int a = stack_get(values); stack_pop(values);

        if (stack_empty(operators)) throw runtime_error("Invalid expression");
        char op = (char)stack_get(operators); stack_pop(operators);

        stack_push(values, apply_operation(a, b, op));
    }

public:
    static int evaluate(const string& expression) {
        Stack* values = stack_create();
        Stack* operators = stack_create();
        istringstream iss(expression);
        char token;

        while (iss >> token) {
            if (isdigit(token)) {
                iss.putback(token);
                int num;
                iss >> num;
                stack_push(values, num);
            }
            else if (token == '(') {
                stack_push(operators, token);
            }
            else if (token == ')') {
                while (!stack_empty(operators) && (char)stack_get(operators) != '(') {
                    process_operator(values, operators);
                }
                if (stack_empty(operators)) {
                    stack_delete(values);
                    stack_delete(operators);
                    throw runtime_error("Mismatched parentheses");
                }
                stack_pop(operators);
            }
            else if (token == '+' || token == '-' || token == '*' || token == '/') {
                while (!stack_empty(operators) &&
                    precedence((char)stack_get(operators)) >= precedence(token) &&
                    (char)stack_get(operators) != '(') {
                    process_operator(values, operators);
                }
                stack_push(operators, token);
            }
        }

        while (!stack_empty(operators)) {
            if ((char)stack_get(operators) == '(') {
                stack_delete(values);
                stack_delete(operators);
                throw runtime_error("Mismatched parentheses");
            }
            process_operator(values, operators);
        }
        if (stack_empty(values)) {
            stack_delete(values);
            stack_delete(operators);
            throw runtime_error("Invalid expression");
        }
        int result = stack_get(values);
        stack_pop(values);
        if (!stack_empty(values)) {
            stack_delete(values);
            stack_delete(operators);
            throw runtime_error("Invalid expression");
        }

        stack_delete(values);
        stack_delete(operators);
        return result;
    }
};
void process_expression(const string& expression) {
    try {
        int result = Calculator::evaluate(expression);
        cout << "Result: " << result << endl;
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}
void process_input_stream(istream& input, bool is_interactive) {
    string expression;
    while (true) {
        if (is_interactive) {
            cout << "Enter expression: ";
        }

        if (!getline(input, expression)) {
            break;
        }

        if (expression.empty()) {
            if (is_interactive) break;
            else continue;
        }
        if (!is_interactive) {
            cout << "Expression: " << expression << endl;
        }
        process_expression(expression);

        if (!is_interactive) {
            cout << "-------------------" << endl;
        }
    }
}
int main(int argc, char* argv[]) {
    if (argc == 2) {
        ifstream fin(argv[1]);
        if (!fin) {
            cerr << "Cannot open input file: " << argv[1] << endl;
            return 1;
        }
        process_input_stream(fin, false);
    }
    else {
        process_input_stream(cin, true);
    }

    return 0;
}