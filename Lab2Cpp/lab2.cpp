#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "stack.h"

using namespace std;

int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int apply(char op, int a, int b) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    }
    return 0;
}

void calculate(Stack* values, Stack* ops) {
    char op = static_cast<char>(stack_get(ops));
    stack_pop(ops);

    int right = stack_get(values);
    stack_pop(values);

    int left = stack_get(values);
    stack_pop(values);

    int result = apply(op, left, right);
    stack_push(values, result);
}

void skip_spaces(string& s, size_t& i) {
    while (i < s.size() && isspace(static_cast<char>(s[i])))
    {
        ++i;
    }
}

int scan_int(string& s, size_t& i) {
    int x = 0;
    while (i < s.size() && isdigit(static_cast<char>(s[i]))) {
        x = x * 10 + (s[i] - '0');
        ++i;
    }
    return x;
}

int main(int argc, char* argv[]) {
    ifstream input;
    string s;
    if (argc > 1)
    {
        input.open(argv[1]);
        getline(input, s);
    }

    Stack* values = stack_create();
    Stack* ops = stack_create();

    for (size_t i = 0; i < s.size(); ) {
        skip_spaces(s, i);
        if (i >= s.size()) break;

        char c = s[i];

        if (isdigit(c)) {
            int x = scan_int(s, i);
            stack_push(values, x);
            continue;
        }

        if (c == '(') {
            stack_push(ops, static_cast<int>(c));
            ++i;
            continue;
        }

        if (c == ')') {
            while (!stack_empty(ops) && static_cast<char>(stack_get(ops)) != '(') {
                calculate(values, ops);
            }
            if (!stack_empty(ops) && static_cast<char>(stack_get(ops)) == '(') {
                stack_pop(ops);
            }
            ++i;
            continue;
        }

        if (c == '+' || c == '-' || c == '*' || c == '/') {
            int p = precedence(c);

            while (!stack_empty(ops)) {
                char topop = static_cast<char>(stack_get(ops));
                if (topop == '(' || precedence(topop) < p) break;
                calculate(values, ops);
            }
            stack_push(ops, static_cast<int>(c));
            ++i;
            continue;
        }

        ++i;
    }

    while (!stack_empty(ops)) {
        calculate(values, ops);
    }

    int result = stack_get(values);
    cout << result;

    stack_delete(values);
    stack_delete(ops);
    return 0;
}
