#include <fstream>
#include <stack.h>
#include <cstring>

using namespace std;

#define MAX_STRING_SIZE 1024

int stringToInt(const char* str, int* result) {
    char* endptr;
    errno = 0;

    long num = strtol(str, &endptr, 10);

    if (errno == 34 || num < -2147483647 || num > 2147483647) {
        return -1;
    }

    if (*str == '\0' || *endptr != '\0') {
        return -2;
    }

    *result = (int)num;
    return 0;
}

void operationStack(Stack* stack, const char* strOperation, std::string& output) {
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
    } else if (strcmp(arithmeticMinus, strOperation) == 0) {
        firstInt = stack->get();
        stack->pop();
        secondInt = stack->get();
        stack->pop();
        stack->push(firstInt - secondInt);
    } else if (strcmp(arithmeticMultiplication, strOperation) == 0) {
        firstInt = stack->get();
        stack->pop();
        secondInt = stack->get();
        stack->pop();
        stack->push(firstInt * secondInt);
    } else if (strcmp(arithmeticDivision, strOperation) == 0) {
        firstInt = stack->get();
        stack->pop();
        secondInt = stack->get();
        stack->pop();
        stack->push(firstInt / secondInt);
    } else if (strcmp(arithmeticIntegerDivision, strOperation) == 0) {
        firstInt = stack->get();
        stack->pop();
        secondInt = stack->get();
        stack->pop();
        stack->push(firstInt % secondInt);
    } else if (strcmp(dup, strOperation) == 0) {
        stack->push(stack->get());
    } else if (strcmp(drop, strOperation) == 0) {
        stack->pop();
    } else if (strcmp(swap, strOperation) == 0) {
        firstInt = stack->get();
        stack->pop();
        secondInt = stack->get();
        stack->pop();
        stack->push(firstInt);
        stack->push(secondInt);
    } else if (strcmp(over, strOperation) == 0) {
        firstInt = stack->get();
        stack->pop();
        secondInt = stack->get();
        stack->pop();
        stack->push(secondInt);
        stack->push(firstInt);
        stack->push(secondInt);
    } else if (strcmp(rot, strOperation) == 0) {
        firstInt = stack->get();
        stack->pop();
        secondInt = stack->get();
        stack->pop();
        thirdInt = stack->get();
        stack->pop();
        stack->push(firstInt);
        stack->push(secondInt);
        stack->push(thirdInt);
    } else if (strcmp(dot, strOperation) == 0) {
        output = output + std::to_string(stack->get()) + "\n";
        printf("%d\n", stack->get());
        stack->pop();
    }
}

int readAndExecution(std::ifstream& input, std::string& output) {
    Stack* stack = new Stack();

    size_t lenDataStr = 0;
    char dataStr[MAX_STRING_SIZE] = "";

    int dataInt = 0;

    bool flag = true;
    while (flag) {
        char dataSymbol = input.get();
        if (dataSymbol == ' ' || dataSymbol == EOF) {
            switch (stringToInt(dataStr, &dataInt)) {
                case 0:
                    stack->push(dataInt);
                    break;
                case -2:
                    operationStack(stack, dataStr, output);
                    break;
                case -1:
                    delete stack;
                    return 1;
            }
            lenDataStr = 0;
            dataStr[lenDataStr] = '\0';
        } else {
            dataStr[lenDataStr] = dataSymbol;
            dataStr[++lenDataStr] = '\0';
        }
        if (dataSymbol == EOF) {
            flag = false;
        }
    }

    // delete stack
    delete stack;
    return 0;
}

int test(std::string& output){
    std::string answer = "1\n6\n3\n10\n";
    if (output != answer) {
        return 1;
    }
    return 0;
}

int main(int argc, char **argv) {
    ifstream input(argv[1]);
    string output;
    readAndExecution(input, output);
    input.close();

    // Test
    return test(output);
}