#include <iostream>
#include <string>
#include "stack.h"



// ������� ��� ��������, �������� �� ������ ����������
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*';
}

// ������� ��� ��������� ������������ �������� �� ���������
std::string getAssemblyOperation(char op) {
    if (op == '+') {
        return "ADD";
    }
    else if (op == '-') {
        return "SUB";
    }
    else if (op == '*') {
        return "MUL";
    }    
    else {
        return "";  // �� ��������� ���������� ������ ������
    }
}

// ������� ��� ��������� ���������� ���������
int getPriority(char op) {
    if (op == '(') {
        return 3; // ��������� ������ ���������� ����
    }
    else if (op == '*') {
        return 2;
    }
    else if (op == '+' || op == '-') {
        return 1;
    }
    else {
        return 0;
    }
}

// ������� ��� �������������� ��������������� ��������� � ������������ ���
void convertToAssembly(const std::string& expression) {
    Stack* stack = stack_create();

    for (char c : expression) {
        if (isdigit(c)) {
            std::cout << "PUSH " << c << std::endl;
        }
        else if (isOperator(c)) {
            while (!stack_empty(stack) && getPriority(stack_get(stack)) >= getPriority(c)) {
                if (stack_get(stack) != '(') {
                    std::cout << "POP A\n";
                    std::cout << "POP B\n";
                    std::cout << getAssemblyOperation(stack_get(stack)) << " A, B\n";
                    std::cout << "PUSH A\n";
                }
                stack_pop(stack);
            }
            stack_push(stack, c);
        }
        else if (c == '(') {
            stack_push(stack, c);
        }
        else if (c == ')') {
            while (!stack_empty(stack) && stack_get(stack) != '(') {
                std::cout << "POP A\n";
                std::cout << "POP B\n";
                std::cout << getAssemblyOperation(stack_get(stack)) << " A, B\n";
                std::cout << "PUSH A\n";
                stack_pop(stack);
            }
        }
    }

    while (!stack_empty(stack)) {
        std::cout << "POP A\n";
        std::cout << "POP B\n";
        std::cout << getAssemblyOperation(stack_get(stack)) << " A, B\n";
        std::cout << "PUSH A\n";
        stack_pop(stack);
    }

    stack_delete(stack);
}

int main() {
    std::string expression;
    std::cout << "Enter the arithmetic expression: ";
    getline(std::cin, expression);

    std::cout << "Converting to assembly:" << std::endl;
    convertToAssembly(expression);

    return 0;
}
