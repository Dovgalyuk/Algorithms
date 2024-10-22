#include <iostream>
#include <fstream>
#include "stack.h"
#include "vector.h"
#include <string>

using namespace std;

void handler_numbers(const string& stroka, size_t& i, Stack* numbers);
int handler_operators(char symbol, Stack* numbers);
int handler_command(const string& stroka, size_t& i, Stack* numbers);
void print_stack(Stack* values);

int realization(const string& stroka) {
    Stack* numbers = stack_create();
    bool print = true;
    for (size_t i = 0; i < stroka.length(); i++) {
        if (stroka[i] == ' ') {
            continue;
        }
        if (isdigit(stroka[i])) {
            handler_numbers(stroka, i, numbers);
        }
        else if (stroka[i] == '+' || stroka[i] == '-' || stroka[i] == '*' || stroka[i] == '/' || stroka[i] == '%') {
            if (handler_operators(stroka[i], numbers) != 0) {
                print = false;
            }
        }
        else {
            if (handler_command(stroka, i, numbers) != 0) {
                print = false;
            }
        }
    }
    if (print) {
        print_stack(numbers);
    }
    stack_delete(numbers);
    
    return 0;
}

void handler_numbers(const string& stroka, size_t& i, Stack* numbers) {
    int number = 0;

    while (i < stroka.length() && isdigit(stroka[i])) {
        number = number * 10 + (stroka[i] - '0');
        i++;
    }
    i--;
    stack_push(numbers, number);
}

int handler_operators(char symbol, Stack* numbers) {
    if (stack_size(numbers) < 2) {
        return -1;
    }

    int b = stack_get(numbers);
    stack_pop(numbers);
    int a = stack_get(numbers);
    stack_pop(numbers);
    int result = 0;

    switch (symbol) {
    case '+': result = a + b; break;
    case '-': result = a - b; break;
    case '*': result = a * b; break;
    case '/':
        if (b == 0) {
            return -1;
        }
        result = a / b;
        break;
    case '%': result = a % b; break;
    }
    stack_push(numbers, result);
    return 0;
}

int handler_command(const string& stroka, size_t& i, Stack* numbers) {
    if (stroka.substr(i, 3) == "dup") {
        if (stack_empty(numbers)) {
            return -1;
        }

        int topNumber = stack_get(numbers);
        stack_push(numbers, topNumber);
        i += 2;
    }
    else if (stroka.substr(i, 4) == "drop") {
        if (stack_empty(numbers)) {
            return -1;
        }

        stack_pop(numbers);
        i += 3;
    }
    else if (stroka.substr(i, 4) == "swap") {
        if (stack_size(numbers) < 2) {
            return -1;
        }

        int first = stack_get(numbers);
        stack_pop(numbers);
        int second = stack_get(numbers);
        stack_pop(numbers);
        stack_push(numbers, first);
        stack_push(numbers, second);
        i += 3;
    }
    else if (stroka.substr(i, 4) == "over") {
        if (stack_size(numbers) < 2) {
            return -1;
        }

        int firstNumber = stack_get(numbers);
        stack_pop(numbers);
        int secondNumber = stack_get(numbers);
        stack_push(numbers, firstNumber);
        stack_push(numbers, secondNumber);
        i += 3;
    }
    else if (stroka.substr(i, 3) == "rot") {
        if (stack_size(numbers) < 3) {
            return -1;
        }

        int firstN = stack_get(numbers);
        stack_pop(numbers);
        int secondN = stack_get(numbers);
        stack_pop(numbers);
        int thirdN = stack_get(numbers);
        stack_pop(numbers);
        stack_push(numbers, secondN);
        stack_push(numbers, firstN);
        stack_push(numbers, thirdN);
        i += 2;
    }
    else if (stroka[i] == '.') {
        if (stack_empty(numbers)) {
            return -1;
        }

        int topNumber = stack_get(numbers);
        cout << topNumber << endl;
        stack_pop(numbers);
    }

    return 0;
}

void print_stack(Stack* numbers) {
    while (!stack_empty(numbers)) {
        int topNumber = stack_get(numbers);
        cout << topNumber << endl;
        stack_pop(numbers);
    }
}

int main() {
    ifstream inputFile("input.txt");
    string stroka;

    while (getline(inputFile, stroka)) {
        realization(stroka);
    }

    return 0;
}