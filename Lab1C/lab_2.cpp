#include <iostream>
#include <string>
#include <stack>
#include <cctype>

#include "stack.h"

using namespace std;

bool is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int get_operator_priority(char op) {
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;  // Если не оператор
    }
}

string infix_to_RPN(string& infix) {
    string result;
    Stack* operators = stack_create();

    for (char c : infix) {
        if (isalnum(c))
            result += c;  // Если символ - цифра или буква, добавляем к выходной строке

        else if (is_operator(c)) {
            while (!stack_empty(operators) && get_operator_priority(stack_get(operators)) >= get_operator_priority(c)) {
                result += stack_get(operators);
                stack_pop(operators);
            }
            stack_push(operators, c);
        }
        else if (c == '(') {
            stack_push(operators, c);
        }
        else if (c == ')') {
            while (!stack_empty(operators) && stack_get(operators) != '(') {
                result += stack_get(operators);
                stack_pop(operators);
            }
            stack_pop(operators);  // Убираем '(' со стека
        }
    }

    while (!stack_empty(operators)) {
        result += stack_get(operators);
        stack_pop(operators);
    }

    stack_delete(operators);

    return result;
}

int calculate_expression(string& postfix) {
    Stack* intermediate_values = stack_create();
    
    int temp_value = 0;
    int temp_value_2 = 0;

    for (char c : postfix) {
        if (!is_operator(c))
            stack_push(intermediate_values, c - 48);
        else {
            switch (c)
            {
            case('+'):
                temp_value = stack_get(intermediate_values);
                stack_pop(intermediate_values);
                temp_value += stack_get(intermediate_values);
                stack_pop(intermediate_values);

                stack_push(intermediate_values, temp_value);
                break;

            case('-'):
                temp_value_2 = stack_get(intermediate_values);
                stack_pop(intermediate_values);
                temp_value = (stack_get(intermediate_values));
                stack_pop(intermediate_values);

                stack_push(intermediate_values, temp_value - temp_value_2);
                break;

            case('*'):
                temp_value = stack_get(intermediate_values);
                stack_pop(intermediate_values);
                temp_value *= stack_get(intermediate_values);
                stack_pop(intermediate_values);

                stack_push(intermediate_values, temp_value);
                break;

            case('/'):
                temp_value_2 = stack_get(intermediate_values);
                stack_pop(intermediate_values);
                temp_value = stack_get(intermediate_values);
                stack_pop(intermediate_values);

                stack_push(intermediate_values, temp_value / temp_value_2);
                break;
            }
        }
    }
    temp_value = stack_get(intermediate_values);
    stack_delete(intermediate_values);

    return temp_value;
}

int main()
{
	string input_data;

	cin >> input_data;

    input_data = infix_to_RPN(input_data);

    cout << input_data;

    cout << endl << calculate_expression(input_data);
}