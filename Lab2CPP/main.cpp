#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "stack.h"
#include "vector.h"

using namespace std;

struct CPU {
    int registers[4] = {0, 0, 0, 0}; // Регистры A, B, C, D
    Stack* stack;
    bool error = false;
    
    CPU() {
        stack = stack_create();
    }

    ~CPU() {
        stack_delete(stack);
    }

    void push(int value) {
        stack_push(stack, value);
    }

    void pop(int regIndex) {
        if (stack_empty(stack) || stack_get(stack) < 0) {
            cout << "BAD POP" << endl;
            error = true;
            return;
        }
        registers[regIndex] = stack_get(stack);
        stack_pop(stack);
    }

    void add() {
        if (stack_size(stack) < 2) { cout << "BAD OPERATION" << endl; error = true; return; }
        int a = stack_get(stack); stack_pop(stack);
        int b = stack_get(stack); stack_pop(stack);
        stack_push(stack, a + b);
    }

    void sub() {
        if (stack_size(stack) < 2) { cout << "BAD OPERATION" << endl; error = true; return; }
        int a = stack_get(stack); stack_pop(stack);
        int b = stack_get(stack); stack_pop(stack);
        stack_push(stack, b - a);
    }

    void mul() {
        if (stack_size(stack) < 2) { cout << "BAD OPERATION" << endl; error = true; return; }
        int a = stack_get(stack); stack_pop(stack);
        int b = stack_get(stack); stack_pop(stack);
        stack_push(stack, a * b);
    }

    void call(int address) {
        stack_push(stack, -address); // Отрицательное значение для адреса возврата
    }

    void ret() {
        if (stack_empty(stack) || stack_get(stack) >= 0) {
            cout << "BAD RET" << endl;
            error = true;
            return;
        }
        stack_pop(stack);
    }

    void printRegisters() {
        cout << "A = " << registers[0] << "\nB = " << registers[1] << "\nC = " << registers[2] << "\nD = " << registers[3] << endl;
    }
};

void executeInstructions(istream& input) {
    CPU cpu;
    string line;
    while (getline(input, line)) {
        istringstream iss(line);
        string command;
        iss >> command;
        if (command == "push") {
            int value;
            iss >> value;
            cpu.push(value);
        } else if (command == "pop") {
            char reg;
            iss >> reg;
            int regIndex = reg - 'A';
            if (regIndex < 0 || regIndex > 3) { cout << "INVALID REGISTER" << endl; return; }
            cpu.pop(regIndex);
        } else if (command == "add") {
            cpu.add();
        } else if (command == "sub") {
            cpu.sub();
        } else if (command == "mul") {
            cpu.mul();
        } else if (command == "call") {
            int address = 1; // фиктивный адрес
            cpu.call(address);
        } else if (command == "ret") {
            cpu.ret();
        } else {
            cout << "INVALID COMMAND" << endl;
            return;
        }
        if (cpu.error) return;
    }
    cpu.printRegisters();
}

int main(int argc, char* argv[]) {
    istream* input = &cin;
    ifstream file;
    if (argc >= 2) {
        file.open(argv[1]);
        if (!file) {
            cerr << "Ошибка: не удалось открыть файл " << argv[1] << endl;
            return 1;
        }
        input = &file;
    }
    executeInstructions(*input);
    return 0;
}
