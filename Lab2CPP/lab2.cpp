#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
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
    Stack* return_stack;
    int regA, regB, regC, regD;
    vector<Instruction> program;
    size_t pc;
    bool error;
    string error_message;

    bool is_register(const string& str) {
        return str == "A" || str == "B" || str == "C" || str == "D";
    }

    bool is_number(const string& str) {
        if (str.empty()) return false;


        size_t start = 0;
        if (str[0] == '-') {
            if (str.length() == 1) return false;
            start = 1;
        }

        for (size_t i = start; i < str.length(); i++) {
            if (!isdigit(str[i])) return false;
        }
        return true;
    }

    int get_value(const string& str) {
        if (is_register(str)) {
            if (str == "A") return regA;
            if (str == "B") return regB;
            if (str == "C") return regC;
            if (str == "D") return regD;
        }
        else if (is_number(str)) {
            return stoi(str);
        }
        return 0;
    }

    void set_register(const string& reg, int value) {
        if (reg == "A") regA = value;
        else if (reg == "B") regB = value;
        else if (reg == "C") regC = value;
        else if (reg == "D") regD = value;
    }

    bool pop_two_operands(Data& a, Data& b) {
        if (stack_empty(stack)) {
            return false;
        }
        b = stack_get(stack);
        stack_pop(stack);

        if (stack_empty(stack)) {
            stack_push(stack, b);
            return false;
        }
        a = stack_get(stack);
        stack_pop(stack);
        return true;
    }



public:
    typedef std::vector<std::string> ProgramLines;

    Processor() {
        stack = stack_create();
        return_stack = stack_create();
        regA = regB = regC = regD = 0;
        pc = 0;
        error = false;
    }

    ~Processor() {
        stack_delete(stack);
        stack_delete(return_stack);
    }

    void load_program(const ProgramLines& lines) {
        for (size_t i = 0; i < lines.size(); ++i) {
            istringstream iss(lines[i]);
            string command;
            iss >> command;

            Instruction instr;
            instr.value = 0;

            if (command == "push") {
                instr.type = InstructionType::PUSH;
                if (!(iss >> instr.operand)) {
                    error = true;
                    error_message = "Missing operand for PUSH";
                    return;
                }
            }
            else if (command == "pop") {
                instr.type = InstructionType::POP;
                if (!(iss >> instr.operand)) {
                    error = true;
                    error_message = "Missing operand for POP";
                    return;
                }
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
                if (!(iss >> instr.operand)) {
                    error = true;
                    error_message = "Missing operand for CALL";
                    return;
                }
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

        while (!stack_empty(stack)) stack_pop(stack);
        while (!stack_empty(return_stack)) stack_pop(return_stack);

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

                if (!is_register(instr.operand)) {
                    error = true;
                    error_message = "Invalid register: " + instr.operand;
                    break;
                }

                set_register(instr.operand, stack_get(stack));
                stack_pop(stack);
                pc++;
                break;
            }

            case InstructionType::ADD: {
                Data a, b;
                if (!pop_two_operands(a, b)) {
                    error = true;
                    error_message = "Not enough operands for ADD";
                    break;
                }
                stack_push(stack, a + b);
                pc++;
                break;
            }

            case InstructionType::SUB: {
                Data a, b;
                if (!pop_two_operands(a, b)) {
                    error = true;
                    error_message = "Not enough operands for SUB";
                    break;
                }
                stack_push(stack, a - b);
                pc++;
                break;
            }

            case InstructionType::MUL: {
                Data a, b;
                if (!pop_two_operands(a, b)) {
                    error = true;
                    error_message = "Not enough operands for MUL";
                    break;
                }
                stack_push(stack, a * b);
                pc++;
                break;
            }

            case InstructionType::CALL: {

                stack_push(return_stack, pc + 1);

                int target = get_value(instr.operand);
                if (target < 0 || static_cast<size_t>(target) >= program.size()) {
                    error = true;
                    error_message = "Invalid call address: " + to_string(target);
                    break;
                }
                pc = target;
                break;
            }

            case InstructionType::RET: {
                if (stack_empty(return_stack)) {
                    error = true;
                    error_message = "BAD RET";
                    break;
                }


                pc = stack_get(return_stack);
                stack_pop(return_stack);
                break;
            }
            }
        }

        return !error;
    }

    void print_registers() {
        cout << "A = " << regA << endl;
        cout << "B = " << regB << endl;
        cout << "C = " << regC << endl;
        cout << "D = " << regD << endl;
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