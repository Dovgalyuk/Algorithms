#include "stack.h"
#include <fstream>
#include <iostream>
#include <cctype>

#define UNDERFLOW_ERROR "Stack underflow"

using namespace std;

void catchCommands(istream* input, ostream* output, Stack* stack);
void inputNumber(Stack* stack, int num);
void outputNumber(ostream* output, Stack* stack);
void doubbleNumber(ostream* output, Stack* stack);
void dropNumber(ostream* output, Stack* stack);
void swapNumber(ostream* output, Stack* stack);
void overNumber(ostream* output, Stack* stack);
void rotNumber(ostream* output, Stack* stack);
void operation(ostream* output, Stack* stack, char operation);

int main(int argc, char* argv[])
{
    istream* input = &cin;
    ostream* output = &cout;
    ifstream inputFile;
    ofstream outputFile;

    if (argc == 3) {
        inputFile.open(argv[1]);
        outputFile.open(argv[2]);

        input = &inputFile;
        output = &outputFile;
    }

    Stack* stack = stack_create();
    
    catchCommands(input, output, stack);

    stack_delete(stack);
}

void catchCommands(istream* input, ostream* output, Stack* stack) {
    string command;
    while (*input >> command) {
        if (command.size() == 1 && isdigit(command[0])) {
            inputNumber(stack, command[0] - '0');
        }
        else if (command == ".") {
            outputNumber(output, stack);
        }
        else if (command == "dup") {
            doubbleNumber(output, stack);
        }
        else if (command == "drop") {
            dropNumber(output, stack);
        }
        else if (command == "swap") {
            swapNumber(output, stack);
        }
        else if (command == "over") {
            overNumber(output, stack);
        }
        else if (command == "rot") {
            rotNumber(output, stack);
        }
        else if (command == "+"
              || command == "-"
              || command == "*"
              || command == "/"
              || command == "%"
            ) {
            operation(output, stack, command[0]);
        }
    }
}

void inputNumber(Stack* stack, int num) {
    stack_push(stack, num);
}

void outputNumber(ostream* output, Stack* stack) {
    if (stack_empty(stack)) {
        *output << ".: " << UNDERFLOW_ERROR << endl;
    }
    else {
        *output << stack_get(stack) << endl;
        dropNumber(output, stack);
    }
}

void doubbleNumber(ostream* output, Stack* stack) {
    if (stack_empty(stack)) {
        *output << "dup: " << UNDERFLOW_ERROR << endl;
    }
    else {
        inputNumber(stack, stack_get(stack));
    }
}

void dropNumber(ostream* output, Stack* stack) {
    if (stack_empty(stack)) {
        *output << "drop: " << UNDERFLOW_ERROR << endl;
    }
    else {
        stack_pop(stack);
    }
}

void swapNumber(ostream* output, Stack* stack) {
    bool error = false;
    int num_1 = 0;
    int num_2 = 0;

    if (!stack_empty(stack)) {
        num_1 = stack_get(stack);
        stack_pop(stack);
    }
    else {
        error = true;
    }

    if (!stack_empty(stack) && !error) {
        num_2 = stack_get(stack);
        stack_pop(stack);
    }
    else {
        error = true;
    }

    if (!error) {
        inputNumber(stack, num_1);
        inputNumber(stack, num_2);
    }
    else {
        *output << "swap: " << UNDERFLOW_ERROR << endl;
    }
}

void overNumber(ostream* output, Stack* stack) {
    bool error = false;
    int num_1 = 0;
    int num_2 = 0;

    if (!stack_empty(stack)) {
        num_1 = stack_get(stack);
        stack_pop(stack);
    }
    else {
        error = true;
    }

    if (!stack_empty(stack) && !error) {
        num_2 = stack_get(stack);
        stack_pop(stack);
    }
    else {
        error = true;
    }

    if (!error) {
        inputNumber(stack, num_2);
        inputNumber(stack, num_1);
        inputNumber(stack, num_2);
    }
    else {
        *output << "over: " << UNDERFLOW_ERROR << endl;
    }
}

void rotNumber(ostream* output, Stack* stack) {
    bool error = false;
    int num_1 = 0;
    int num_2 = 0;
    int num_3 = 0;

    if (!stack_empty(stack)) {
        num_1 = stack_get(stack);
        stack_pop(stack);
    }
    else {
        error = true;
    }

    if (!stack_empty(stack) && !error) {
        num_2 = stack_get(stack);
        stack_pop(stack);
    }
    else {
        error = true;
    }

    if (!stack_empty(stack) && !error) {
        num_3 = stack_get(stack);
        stack_pop(stack);
    }
    else {
        error = true;
    }

    if (!error) {
        inputNumber(stack, num_2);
        inputNumber(stack, num_1);
        inputNumber(stack, num_3);
    }
    else {
        *output << "over: " << UNDERFLOW_ERROR << endl;
    }
}

void operation(ostream* output, Stack* stack, char operation) {
    bool error = false;
    int num_1 = 0;
    int num_2 = 0;

    if (!stack_empty(stack)) {
        num_1 = stack_get(stack);
        stack_pop(stack);
    }
    else {
        error = true;
    }

    if (!stack_empty(stack) && !error) {
        num_2 = stack_get(stack);
        stack_pop(stack);
    }
    else {
        error = true;
    }

    int result = 0;

    if (!error) {
        switch (operation) {
            case '+': 
                result = num_2 + num_1;
                break;
            case '-': 
                result = num_2 - num_1;
                break;
            case '*': 
                result = num_2 * num_1;
                break;
            case '/': 
                if (num_1 == 0) {
                    error = true;
                }
                else {
                result = num_2 / num_1;
                }
                break;
            case '%': 
                if (num_1 == 0) {
                    error = true;
                }
                else {
                    result = num_2 % num_1;
                }
        }

        if (error) {
            *output << "Osperation " << operation << ": " << "ZeroDivizion" << endl;
        }
        else {
            inputNumber(stack, result);
        }
    }
    else {
        *output << "Operation " << operation << ": " << UNDERFLOW_ERROR << endl;
    }
}