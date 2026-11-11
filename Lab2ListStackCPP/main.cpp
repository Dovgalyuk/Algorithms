#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include <stdexcept>
#include <initializer_list>
#include "stack.h"

using namespace std;


int priority(char oper);
void calculation(Stack* numbers, Stack* opers);
void deleteStacks(initializer_list<Stack*> stacks);

int main(int argc, char* argv[]){
    if (argc != 2)
    {
        cout << "usage: main <input_file>";
        return 1;
    }

    ifstream input(argv[1]);

    if (!input)
    {
        std::cout << "cannot open file";
        return 1;
    }

    string expression;
    input >> expression;

    Stack* numbers = stack_create();
    Stack* opers = stack_create();

    try {
        string number = "";
        bool expectOperand = true;

        for(size_t i = 0; i < expression.length(); i++){
            if(isdigit(expression[i])){

                if(!expectOperand && number == ""){
                    throw runtime_error("incorrect expression");
                }

                number += expression[i];
            }
            else{
                if(number != ""){
                    stack_push(numbers, stoi(number));
                    number = "";
                    expectOperand = false;
                }

                if (expression[i] == '(') {

                    if(!expectOperand){
                        throw runtime_error("incorrect expression");
                    }

                    expectOperand = true;
                    stack_push(opers, expression[i]);
                }
                else if (expression[i] == ')') {

                    if(expectOperand){
                        throw runtime_error("incorrect expression");
                    }

                    while (!stack_empty(opers) && stack_get(opers) != '(') {
                        calculation(numbers, opers);
                    }

                    if (stack_empty(opers)) {
                        throw runtime_error("incorrect brackets");
                    }

                    stack_pop(opers);
                    expectOperand = false;
                }
                else {

                    if(expectOperand){
                        throw runtime_error("incorrect expression");
                    }

                    while (!stack_empty(opers) &&
                        stack_get(opers) != '(' &&
                        priority(expression[i]) <= priority(stack_get(opers)))
                    {
                        calculation(numbers, opers);
                    }

                    stack_push(opers, expression[i]);
                    expectOperand = true;
                }
            }
        }

        if(number != ""){
            stack_push(numbers, stoi(number));
            number = "";
            expectOperand = false;
        }

        if(expectOperand){
            throw runtime_error("incorrect expression");
        }

        while (!stack_empty(opers)) {
            if (stack_get(opers) == '(' || stack_get(opers) == ')') {
                throw runtime_error("incorrect brackets");
            }

            calculation(numbers, opers);
        }

        if (stack_empty(numbers)) {
            throw runtime_error("incorrect expression");
        }

        cout << stack_get(numbers);

        deleteStacks({opers, numbers});
    }
    catch (const exception& error) {
        cout << "error: " << error.what() << endl;

        deleteStacks({opers, numbers});
    }

    return 0;
}

void deleteStacks(initializer_list<Stack*> stacks) {
    for (Stack* stack : stacks) {
        stack_delete(stack);
    }
}

int priority(char oper){
    if(oper == '+' || oper == '-')
        return 1;

    if(oper == '*' || oper == '/')
        return 2;

    throw runtime_error("unknown operator");
}

void calculation(Stack* numbers, Stack* opers){
    if(stack_empty(numbers)){
        throw runtime_error("incorrect expression");
    }
    
    int a = stack_get(numbers);
    stack_pop(numbers);

    if(stack_empty(numbers)){
        throw runtime_error("incorrect expression");
    }

    int b = stack_get(numbers);
    stack_pop(numbers);

    char oper = stack_get(opers);
    stack_pop(opers);

    switch (oper)
    {
    case '+':
        stack_push(numbers, a+b);
        break;
    case '-':
        stack_push(numbers, b-a);
        break;
    case '*':
        stack_push(numbers, a*b);
        break;
    case '/':
        if(a == 0){
            throw runtime_error("division by zero");
        }
        stack_push(numbers, b/a);
        break;

    default:
        throw runtime_error("unknown operator");
    }
}