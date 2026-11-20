#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "stack.h"
#include "machine.h"
#include <string>

using namespace std;

struct Instruction {
    string operation;
    int argument;
};

struct Machine {
    Stack* stack;
    Instruction* data;
    int size;
    int current_instruction;
    int vars[4];
};

Data make_value(int value) {
    return { value, false };
}

Data make_return_address(int value) {
    return { value, true };
}

typedef void (*InstructionFunc)(Machine*);
unordered_map<string, InstructionFunc> list_instructions = {
    {"bipush", bipush},
    {"pop", pop},
    {"imul", imul},
    {"iand", iand},
    {"ior", ior},
    {"ixor", ixor},
    {"iadd", iadd},
    {"isub", isub},
    {"iload_0", iload},
    {"iload_1", iload},
    {"iload_2", iload},
    {"iload_3", iload},
    {"istore_0", istore},
    {"istore_1", istore},
    {"istore_2", istore},
    {"istore_3", istore},
    {"swap", swap_stack},
    {"invokestatic", invokestatic},
    {"return", return_}
};

Machine* machine_create() {
    Machine* machine = new Machine;
    machine->stack = stack_create();
    machine->data = nullptr;
    machine->size = 0;
    machine->current_instruction = 0;
    for (int i = 0; i < 4; i++) {
        machine->vars[i] = 0;
    }
    return machine;
}

void machine_delete(Machine* machine) {
    stack_delete(machine->stack);
    delete[] machine->data;
    delete machine;
}

Machine* machine_read(Machine* machine, string file) {
    int count = 0;
    ifstream input(file);
    if (!input.is_open()) {
        throw runtime_error("cannot open file: " + file);
    }
    string line;
    while (getline(input, line)) count++;
    input.clear();
    input.seekg(0);
    machine->size = count;
    machine->data = new Instruction[count];
    for (int i = 0; i < count; i++) {
        Instruction instruction;
        getline(input, line);
        stringstream instr(line);
        string operation, arg;
        int argument;
        instr >> operation;
        instr >> arg;
        if (!arg.empty()) {
            argument = stoi(arg);
        }
        else {
            argument = 0;
        }
        instruction.argument = argument;
        instruction.operation = operation;
        machine->data[i] = instruction;
    }
    return machine;
}

Machine* machine_run(Machine* machine) {
    while (machine->current_instruction < machine->size) {
        Instruction instruction = machine->data[machine->current_instruction];
        if (list_instructions.find(instruction.operation) == list_instructions.end())
            throw runtime_error("unknown operation: " + instruction.operation);
        cout << instruction.operation << endl;
        InstructionFunc operation = list_instructions[instruction.operation];
        operation(machine);
    }
    return machine;
}

void bipush(Machine* machine) {
    int argument = machine->data[machine->current_instruction].argument;
    stack_push(machine->stack, make_value(argument));
    machine->current_instruction++;
}

void pop(Machine* machine) {
    if (stack_empty(machine->stack))
        throw runtime_error("pop: stack is empty");
    if (stack_get(machine->stack).is_return_address)
        throw runtime_error("pop: return address");
    stack_pop(machine->stack);
    machine->current_instruction++;
}

int light_value(Stack* stack, string operation){
    if (stack_empty(stack))
        throw runtime_error(operation + ": stack is empty");
    Data value = stack_get(stack);
    if (value.is_return_address)
        throw runtime_error(operation + ": return address");
    stack_pop(stack);
    return value.value;
}

void imul(Machine* machine) {
    Stack* stack = machine->stack;
    int a1 = light_value(stack, "imul");
    int a2 = light_value(stack, "imul");
    stack_push(stack, make_value(a1 * a2));
    machine->current_instruction++;
}

void iand(Machine* machine) {
    Stack* stack = machine->stack;
    int a1 = light_value(stack, "iand");
    int a2 = light_value(stack, "iand");
    stack_push(stack, make_value(a1 & a2));
    machine->current_instruction++;
}

void ior(Machine* machine) {
    Stack* stack = machine->stack;
    int a1 = light_value(stack, "ior");
    int a2 = light_value(stack, "ior");
    stack_push(stack, make_value(a1 | a2));
    machine->current_instruction++;
}

void ixor(Machine* machine) {
    Stack* stack = machine->stack;
    int a1 = light_value(stack, "ixor");
    int a2 = light_value(stack, "ixor");
    stack_push(stack, make_value(a1 ^ a2));
    machine->current_instruction++;
}

void iadd(Machine* machine) {
    Stack* stack = machine->stack;
    int a1 = light_value(stack, "iadd");
    int a2 = light_value(stack, "iadd");
    stack_push(stack, make_value(a1 + a2));
    machine->current_instruction++;
}

void isub(Machine* machine) {
    Stack* stack = machine->stack;
    int a1 = light_value(stack, "isub");
    int a2 = light_value(stack, "isub");
    stack_push(stack, make_value(a2 - a1));
    machine->current_instruction++;
}

void iload(Machine* machine) {
    string oper = machine->data[machine->current_instruction].operation;
    char last = oper.back();
    stack_push(machine->stack, make_value(machine->vars[last - '0']));
    machine->current_instruction++;
}

void istore(Machine* machine) {
    Stack* stack = machine->stack;
    if (stack_empty(stack))
        throw runtime_error("istore: stack is empty");
    Data a1 = stack_get(stack);
    if (a1.is_return_address)
        throw runtime_error("istore: return address");
    stack_pop(stack);
    string oper = machine->data[machine->current_instruction].operation;
    char last = oper.back();
    machine->vars[last - '0'] = a1.value;
    machine->current_instruction++;
}

void swap_stack(Machine* machine) {
    Stack* stack = machine->stack;
    if (stack_empty(stack))
        throw runtime_error("swap_stack: stack is empty");
    Data a1 = stack_get(stack);
    if (a1.is_return_address)
        throw runtime_error("swap_stack: return address");
    stack_pop(stack);
    if (stack_empty(stack))
        throw runtime_error("swap_stack: stack is empty");
    Data a2 = stack_get(stack);
    if (a2.is_return_address)
        throw runtime_error("swap_stack: return address");
    stack_pop(stack);
    stack_push(stack, a1);
    stack_push(stack, a2);
    machine->current_instruction++;
}

void invokestatic(Machine* machine) {
    int argument = machine->data[machine->current_instruction].argument;
    if (argument < 0 || argument >= machine->size)
        throw runtime_error("invokestatic: invalid address");
    stack_push(machine->stack, make_return_address(machine->current_instruction + 1));
    machine->current_instruction = argument;
}

void return_(Machine* machine) {
    Stack* stack = machine->stack;
    if (stack_empty(stack))
        throw runtime_error("return: no return address");
    Data value = stack_get(stack);
    if (!value.is_return_address)
        throw runtime_error("return: expected return address");
    stack_pop(stack);
    machine->current_instruction = value.value;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "Input file not specified" << endl;
        return 1;
    }
    Machine* machine = machine_create();
    try {
        machine_read(machine, argv[1]);
        machine_run(machine);
    }
    catch (const runtime_error& e) {
        cout << "error: " << e.what() << endl;
        machine_delete(machine);
        return 1;
    }
    cout << "stack:" << endl;
    stack_print(machine->stack);
    cout << "vars:" << endl;
    for (int i = 0; i < 4; i++) {
        cout << machine->vars[i] << endl;
    }
    machine_delete(machine);
    return 0;
}