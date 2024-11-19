#include <fstream>
#include <iostream>
#include <stack.h>

#include "array.h"
using namespace std;

#define MAX_STRING_SIZE 1024

int stringToInt(const char* str, int* result) {
    char* endptr;
    errno = 0;

    long num = strtol(str, &endptr, 10);

    if (errno == ERANGE || num < INT_MIN || num > INT_MAX) {
        return -1;
    }

    if (*str == '\0' || *endptr != '\0') {
        return -2;
    }

    *result = (int)num;
    return 0;
}

void operationStack(Stack* stack, const char* strOperation) {
    int firstInt = 0;
    int secondInt = 0;
    int thirdInt = 0;

    const char *arithmeticPlus = "+";
    const char *arithmeticMinus = "-";
    const char *arithmeticMultiplication = "*";
    const char *arithmeticDivision = "/";
    const char *arithmeticIntegerDivision = "%";
    const char *dup = "dup";
    const char *drop = "drop";
    const char *swap = "swap";
    const char *over = "over";
    const char *rot = "rot";
    const char *dot = ".";

    // Arithmetic
    if (strcmp(arithmeticPlus, strOperation) == 0) {
        firstInt = stack->get();
        stack->pop();
        secondInt = stack->get();
        stack->pop();
        stack->push(firstInt + secondInt);
    }
    if (strcmp(arithmeticMinus, strOperation) == 0) {
        firstInt = stack->get();
        stack->pop();
        secondInt = stack->get();
        stack->pop();
        stack->push(firstInt - secondInt);
    }
    if (strcmp(arithmeticMultiplication, strOperation) == 0) {
        firstInt = stack->get();
        stack->pop();
        secondInt = stack->get();
        stack->pop();
        stack->push(firstInt * secondInt);
    }
    if (strcmp(arithmeticDivision, strOperation) == 0) {
        firstInt = stack->get();
        stack->pop();
        secondInt = stack->get();
        stack->pop();
        stack->push(firstInt / secondInt);
    }
    if (strcmp(arithmeticIntegerDivision, strOperation) == 0) {
        firstInt = stack->get();
        stack->pop();
        secondInt = stack->get();
        stack->pop();
        stack->push(firstInt % secondInt);
    }

    // Other
    if (strcmp(dup, strOperation) == 0) {
        stack->push(stack->get());
    }
    if (strcmp(drop, strOperation) == 0) {
        stack->pop();
    }
    if (strcmp(swap, strOperation) == 0) {
        firstInt = stack->get();
        stack->pop();
        secondInt = stack->get();
        stack->pop();
        stack->push(firstInt);
        stack->push(secondInt);
    }
    if (strcmp(over, strOperation) == 0) {
        firstInt = stack->get();
        stack->pop();
        secondInt = stack->get();
        stack->pop();
        stack->push(secondInt);
        stack->push(firstInt);
        stack->push(secondInt);
    }
    if (strcmp(rot, strOperation) == 0) {
        firstInt = stack->get();
        stack->pop();
        secondInt = stack->get();
        stack->pop();
        thirdInt = stack->get();
        stack->pop();
        stack->push(firstInt);
        stack->push(secondInt);
        stack->push(thirdInt);
    }
    if (strcmp(dot, strOperation) == 0) {
        printf("%d\n", stack->get());
        stack->pop();
    }
}

int readAndExecution(std::ifstream& input) {
    Stack* stack = new Stack();
    int dataStatus = 0;
    char dataStr[MAX_STRING_SIZE] = "";
    size_t lenDataStr = 0;
    int dataInt = 0;
    char dataSymbol;

    while (input.get(dataSymbol)) {
        if (dataSymbol != ' ') {
            dataStr[lenDataStr] = dataSymbol;
            dataStr[++lenDataStr] = '\0';
        } else {
            dataStatus = stringToInt(dataStr, &dataInt);
            switch (dataStatus) {
                case 0:
                    stack->push(dataInt);
                    break;
                case -2:
                    operationStack(stack, dataStr);
                    break;
                case -1:
                    return 1;
            }
            lenDataStr = 0;
            dataStr[lenDataStr] = '\0';
            if (dataSymbol == '\0') {
                break;
            }
        }
    }
    if (lenDataStr != 0) {
        dataStatus = stringToInt(dataStr, &dataInt);
        switch (dataStatus) {
            case 0:
                stack->push(dataInt);
            break;
            case -2:
                operationStack(stack, dataStr);
            break;
            case -1:
                return 1;
        }
    }

    // delete stack
    delete stack;
    return 0;
}

bool test(ifstream& output){
    int number;
    int counter = 0;
    int answer[4] = {1, 6, 3, 10};

    while (output >> number) {
        if (counter + 1 > 4) {
            return true;
        }
        if (answer[counter++] != number) {
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv) {
    ifstream input(argv[1]);
    FILE *outputWrite = freopen(argv[2], "w", stdout);

    readAndExecution(input);

    fclose(outputWrite);
    input.close();

    // Test
    ifstream output(argv[2]);

    if (test(output)) {
        input.close();
        output.close();
        return 1;
    }
    output.close();
    return 0;
}