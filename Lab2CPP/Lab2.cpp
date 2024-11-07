#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include "stack.h"

enum class CommandType { PUSH, POP, CALL, RET, INVALID };

struct Command {
    CommandType type;
    size_t value;
};

Command parseCommand(const std::string& input) {
    Command cmd = { CommandType::INVALID, 0 };
    std::istringstream iss(input);
    std::string operation;
    iss >> operation;

    if (operation == "push") {
        cmd.type = CommandType::PUSH;
        iss >> cmd.value;
    } else if (operation == "pop") {
        cmd.type = CommandType::POP;
        std::string reg;
        iss >> reg;
        cmd.value = reg[0];
    } else if (operation == "call") {
        cmd.type = CommandType::CALL;
    } else if (operation == "ret") {
        cmd.type = CommandType::RET;
    }

    return cmd;
}

bool isValidRegister(char reg) {
    return reg >= 'A' && reg <= 'D';
}

int main(int argc, char* argv[]) {
    
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

    Stack* stack = stack_create();
    std::map<char, size_t> registers = { {'A', 0}, {'B', 0}, {'C', 0}, {'D', 0} };
    const size_t CALL_MARKER = static_cast<size_t>(-1);

    std::string input;
    while (std::getline(inputFile, input)) {
        Command cmd = parseCommand(input);

        switch (cmd.type) {
            case CommandType::PUSH: {
                stack_push(stack, cmd.value);
                break;
            }
            case CommandType::POP: {
                if (stack_empty(stack)) {
                    std::cout << "BAD POP" << std::endl;
                    inputFile.close();
                    stack_delete(stack);
                    return 1;
                }

                size_t value = stack_get(stack);
                if (value == CALL_MARKER || !isValidRegister(static_cast<char>(cmd.value))) {
                    std::cout << "BAD POP" << std::endl;
                    inputFile.close();
                    stack_delete(stack);
                    return 1;
                }

                registers[static_cast<char>(cmd.value)] = value;
                stack_pop(stack);
                break;
            }
            case CommandType::CALL: {
                stack_push(stack, CALL_MARKER);
                break;
            }
            case CommandType::RET: {
                if (stack_empty(stack) || stack_get(stack) != CALL_MARKER) {
                    std::cout << "BAD RET" << std::endl;
                    inputFile.close();
                    stack_delete(stack);
                    return 1;
                }
                stack_pop(stack);
                break;
            }
            case CommandType::INVALID: {
                std::cout << "Invalid command!" << std::endl;
                inputFile.close();
                stack_delete(stack);
                return 1;
            }
        }
    }

    for (const auto& reg : registers) {
        std::cout << reg.first << " = " << reg.second << std::endl;
    }

    inputFile.close();
    stack_delete(stack);
    return 0;
}
