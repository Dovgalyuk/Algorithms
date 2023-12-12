#include <iostream>
#include <sstream>
#include <vector>
#include "stack.h"
#include "list.h"

using namespace std;

bool evaluateExpression(const vector<string>& expression) {
    Stack* stack = stack_create();
    int k = 0;
    for (const string& token : expression) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            stack_push(stack, stod(token));
            k++;
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (stack_empty(stack)) {
                cout << "UNDERFLOW" << endl;
                stack_delete(stack);
                return false;
            }

            double operand2 = stack_get(stack);
            stack_pop(stack);

            if (stack_empty(stack)) {
                cout << "UNDERFLOW" << endl;
                stack_delete(stack);
                return false;
            }

            double operand1 = stack_get(stack);
            stack_pop(stack);

            if (token == "/" && operand2 == 0) {
                cout << "ZERO" << endl;
                stack_delete(stack);
                return false;
            }

            if (token == "+") {
                stack_push(stack, operand1 + operand2);
            }
            else if (token == "-") {
                stack_push(stack, operand1 - operand2);
            }
            else if (token == "*") {
                stack_push(stack, operand1 * operand2);
            }
            else if (token == "/") {
                stack_push(stack, operand1 / operand2);
            }
            k--;
        }
    }

    if (!stack_empty(stack) && k>1){
        cout << "OVERFLOW" << endl;
        stack_delete(stack);
        return false;
    }

    stack_delete(stack);
    return true;
}

int main() {
    setlocale(LC_ALL, "rus");
    cout << "Введите символы через пробел: ";
    string input1;
    getline(cin, input1);
    istringstream iss1(input1);
    vector<string> expression1(istream_iterator<string>{iss1}, istream_iterator<string>{});

    

    if (evaluateExpression(expression1)) {
        cout << "OK" << endl;
    }


    return 0;
}