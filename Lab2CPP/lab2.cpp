#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

#include "stack.h"
using namespace std;

enum InstructionType {
    PUSH,
    POP,
    ADD,
    SUB,
    MUL,
    CALL,
    RET,
    INVALID
};

InstructionType getInstructionType(const string& instruction) {
    if (instruction == "push") return PUSH;
    if (instruction == "pop") return POP;
    if (instruction == "add") return ADD;
    if (instruction == "sub") return SUB;
    if (instruction == "mul") return MUL;
    if (instruction == "call") return CALL;
    if (instruction == "ret") return RET;
    return INVALID;
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    Stack* stack = stack_create();
    map<string, int> registers;
    registers["A"] = 0;
    registers["B"] = 0;
    registers["C"] = 0;
    registers["D"] = 0;


    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string instruction;
        ss >> instruction;

        InstructionType type = getInstructionType(instruction);

        switch (type) {
            case PUSH: {
                string valueStr;
                ss >> valueStr;
                try {
                    Data value = stoi(valueStr);
                    stack_push(stack, value);
                } catch (const invalid_argument& e) {
                   
                   if (registers.count(valueStr)) {
                     stack_push(stack, registers[valueStr]);
                   }
                   else {
                    cerr << "Error: Invalid push argument." << endl;
                    stack_delete(stack);
                    return 1;
                   }
                }
                break;
            }
            case POP: {
                string registerName;
                ss >> registerName;

                if (stack_empty(stack)) {
                    cerr << "Error: Stack is empty during pop." << endl;
                    stack_delete(stack);
                    return 1;
                }
                
                Data top = stack_get(stack);
                if (top > 10000){ 
                  cerr << "Error: Cannot pop return address." << endl;
                  stack_delete(stack);
                  return 1;
                }

                if (!registers.count(registerName)) {
                    cerr << "Error: Invalid register name." << endl;
                    stack_delete(stack);
                    return 1;
                }

                registers[registerName] = top;
                stack_pop(stack);
                break;
            }
            case ADD:
            case SUB:
            case MUL: {
                if (stack_empty(stack)) {
                    cerr << "Error: Stack is empty during arithmetic operation." << endl;
                    stack_delete(stack);
                    return 1;
                }
                Data operand2 = stack_get(stack);
                stack_pop(stack);

                if (stack_empty(stack)) {
                    cerr << "Error: Stack is empty during arithmetic operation." << endl;
                    stack_delete(stack);
                    return 1;
                }
                Data operand1 = stack_get(stack);
                stack_pop(stack);

                Data result;
                if (type == ADD) {
                    result = operand1 + operand2;
                } else if (type == SUB) {
                    result = operand1 - operand2;
                } else {
                    result = operand1 * operand2;
                }
                stack_push(stack, result);
                break;
            }
            case CALL: {
                Data returnAddress = 10001;
                stack_push(stack, returnAddress);
                break;
            }
            case RET: {
                if (stack_empty(stack)) {
                    cerr << "Error: Stack is empty during ret." << endl;
                    stack_delete(stack);
                    return 1;
                }
                Data top = stack_get(stack);

                 if (top != 10001){
                    cerr << "BAD RET" << endl;
                    stack_delete(stack);
                    return 1;
                 }

                stack_pop(stack);
                break;
            }
            case INVALID:
                cerr << "Error: Invalid instruction." << endl;
                stack_delete(stack);
                return 1;
        }
    }

    stack_delete(stack);
    inputFile.close();

    for (const auto& pair : registers) {
        cout << pair.first << " = " << pair.second << endl;
    }

    return 0;
}
