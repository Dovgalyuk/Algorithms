#include <iostream>
#include <string>
#include "stack.h"  
using namespace std;

// ������� ��� ��������, �������� �� ������ ����������
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*';
}

// ������� ��� ��������� ������������ �������� �� ���������
string getOperation(char op) {
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
void convertToAssembly(const string& expression) {
    Stack* stack = stack_create();  // �������� ����� ��� �������� ����������

    for (char c : expression) {
        if (isdigit(c)) {
            cout << "PUSH " << c << endl;  // ����� ���������� ��� ���������� ����� � ����
        }
        else if (isOperator(c)) {
            while (!stack_empty(stack) && getPriority(stack_get(stack)) >= getPriority(c)) {                
                stack_pop(stack);  // ������������ ���������� � ����� ������� �����������
            }
            stack_push(stack, c);  // ���������� �������� ��������� � ����
        }
        else if (c == '(') {
            stack_push(stack, c);  // ���������� ����������� ������ � ����
        }
        else if (c == ')') {
            while (!stack_empty(stack) && stack_get(stack) != '(') {
                cout << "POP A\n";
                cout << "POP B\n";
                cout << getOperation(stack_get(stack)) << " A, B\n";  // ��������� ���� ��� ��������
                cout << "PUSH A\n";
                stack_pop(stack);  // ������������ ��������� �� �����
            }
            if (!stack_empty(stack) && stack_get(stack) == '(') {
                stack_pop(stack);  // �������� ����������� ������ �� �����
            }
        }
    }

    while (!stack_empty(stack)) {
        cout << "POP A\n";
        cout << "POP B\n";
        cout << getOperation(stack_get(stack)) << " A, B\n";  // ��������� ���� ��� ��������
        cout << "PUSH A\n";
        stack_pop(stack);  // ������������ ��������� �� �����
    }

    stack_delete(stack);  // ������������ ������, ���������� ��� �����
}

int main() {
    string expression;
    cout << "Enter the arithmetic expression: ";
    getline(cin, expression);  // ���� ��������������� ���������

    cout << "Converting to assembly:" << endl;
    convertToAssembly(expression);  // ����� ������� �������������� � ������������ ���

    return 0;
}
