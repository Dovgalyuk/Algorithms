#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "stack.h"

using namespace std;

enum class InstructionType {
    PUSH,
    POP,
    ADD,
    SUB,
    MUL,
    CALL,
    RET
};

struct Instruction {
    InstructionType type;
    string operand;
    int value;
};

class Processor {
private:
    Stack* stack;
    map<string, int> registers;
    vector<Instruction> program;
    size_t pc;
    bool error;
    string error_message;

    bool is_register(const string& str) {
        return str == "A" || str == "B" || str == "C" || str == "D";
    }

    bool is_number(const string& str) {
        istringstream iss(str);
        int value;
        return (iss >> value) && iss.eof();
    }

    int get_value(const string& str) {
        if (is_register(str)) {
            return registers[str];
        }
        else if (is_number(str)) {
            return stoi(str);
        }
        return 0;
    }

    bool stack_has_at_least(int count) {
        Stack* temp = stack_create();
        int size = 0;

        while (!stack_empty(stack)) {
            stack_push(temp, stack_get(stack));
            stack_pop(stack);
            size++;
            if (size >= count) break;
        }

        while (!stack_empty(temp)) {
            stack_push(stack, stack_get(temp));
            stack_pop(temp);
        }

        stack_delete(temp);
        return size >= count;
    }

public:
    Processor() {
        stack = stack_create();
        registers = { {"A", 0}, {"B", 0}, {"C", 0}, {"D", 0} };
        pc = 0;
        error = false;
    }

    ~Processor() {
        stack_delete(stack);
    }

    void load_program(const vector<string>& lines) {
        for (size_t i = 0; i < lines.size(); ++i) {
            istringstream iss(lines[i]);
            string command;
            iss >> command;

            Instruction instr;
            instr.value = 0;

            if (command == "push") {
                instr.type = InstructionType::PUSH;
                iss >> instr.operand;
            }
            else if (command == "pop") {
                instr.type = InstructionType::POP;
                iss >> instr.operand;
            }
            else if (command == "add") {
                instr.type = InstructionType::ADD;
            }
            else if (command == "sub") {
                instr.type = InstructionType::SUB;
            }
            else if (command == "mul") {
                instr.type = InstructionType::MUL;
            }
            else if (command == "call") {
                instr.type = InstructionType::CALL;
            }
            else if (command == "ret") {
                instr.type = InstructionType::RET;
            }
            else {
                error = true;
                error_message = "Unknown command: " + command;
                return;
            }

            program.push_back(instr);
        }
    }

    bool execute() {
        pc = 0;
        error = false;

        while (pc < program.size() && !error) {
            const Instruction& instr = program[pc];

            switch (instr.type) {
            case InstructionType::PUSH: {
                int value = get_value(instr.operand);
                stack_push(stack, value);
                pc++;
                break;
            }

            case InstructionType::POP: {
                if (stack_empty(stack)) {
                    error = true;
                    error_message = "Stack underflow";
                    break;
                }

                Data top = stack_get(stack);
                if (top < 0) {
                    error = true;
                    error_message = "Cannot pop return address";
                    break;
                }

                if (!is_register(instr.operand)) {
                    error = true;
                    error_message = "Invalid register: " + instr.operand;
                    break;
                }

                registers[instr.operand] = stack_get(stack);
                stack_pop(stack);
                pc++;
                break;
            }

            case InstructionType::ADD: {
                if (!stack_has_at_least(2)) {
                    error = true;
                    error_message = "Not enough operands for ADD";
                    break;
                }

                Data b = stack_get(stack);
                stack_pop(stack);
                Data a = stack_get(stack);
                stack_pop(stack);
                stack_push(stack, a + b);
                pc++;
                break;
            }

            case InstructionType::SUB: {
                if (!stack_has_at_least(2)) {
                    error = true;
                    error_message = "Not enough operands for SUB";
                    break;
                }

                Data b = stack_get(stack);
                stack_pop(stack);
                Data a = stack_get(stack);
                stack_pop(stack);
                stack_push(stack, a - b);
                pc++;
                break;
            }

            case InstructionType::MUL: {
                if (!stack_has_at_least(2)) {
                    error = true;
                    error_message = "Not enough operands for MUL";
                    break;
                }

                Data b = stack_get(stack);
                stack_pop(stack);
                Data a = stack_get(stack);
                stack_pop(stack);
                stack_push(stack, a * b);
                pc++;
                break;
            }

            case InstructionType::CALL: {
                stack_push(stack, -(static_cast<Data>(pc) + 1));
                pc++;
                break;
            }

            case InstructionType::RET: {
                if (stack_empty(stack)) {
                    error = true;
                    error_message = "BAD RET";
                    break;
                }

                Data top = stack_get(stack);
                if (top >= 0) {
                    error = true;
                    error_message = "BAD RET";
                    break;
                }

                pc = -top;
                stack_pop(stack);
                break;
            }
            }
        }

        return !error;
    }

    void print_registers() {
        cout << "A = " << registers["A"] << endl;
        cout << "B = " << registers["B"] << endl;
        cout << "C = " << registers["C"] << endl;
        cout << "D = " << registers["D"] << endl;
    }

    void print_error() {
        cout << error_message << endl;
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open()) {
        cerr << "Cannot open file: " << argv[1] << endl;
        return 1;
    }

    vector<string> program;
    string line;

    while (getline(file, line)) {
        if (!line.empty()) {
            program.push_back(line);
        }
    }

    file.close();

    Processor processor;
    processor.load_program(program);

    if (processor.execute()) {
        processor.print_registers();
    }
    else {
        processor.print_error();
    }

    return 0;
}