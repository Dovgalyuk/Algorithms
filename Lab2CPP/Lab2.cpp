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

int main() {
    Stack* stack = stack_create();
    std::map<char, size_t> registers = { {'A', 0}, {'B', 0}, {'C', 0}, {'D', 0} };
    std::string input;

    //использование относительного пути у меня не работает, поэтому использую абсолютный путь
    //но также оставил строку для использования относительного пути
    //файл с входными данными находится: LibraryCPP -> "input2.txt"
    std::ifstream inputFile("D:\\Algorithms-1\\LibraryCPP\\input2.txt");
    //std::ifstream inputFile("../LibraryCPP/input2.txt");
    
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

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
                    stack_delete(stack);
                    return 1;
                }
                if (stack_get(stack) == 0) {
                    std::cout << "BAD POP" << std::endl;
                    stack_delete(stack);
                    return 1;
                }
                if (!isValidRegister(static_cast<char>(cmd.value))) {
                    std::cout << "BAD POP" << std::endl;
                    stack_delete(stack);
                    return 1;
                }
                size_t value = stack_get(stack);
                registers[static_cast<char>(cmd.value)] = value;
                stack_pop(stack);
                break;
            }

            case CommandType::CALL: {
                stack_push(stack, 0);
                break;
            }

            case CommandType::RET: {
                if (stack_empty(stack)) {
                    std::cout << "BAD RET" << std::endl;
                    stack_delete(stack);
                    return 1;
                }
                if (stack_get(stack) != 0) {
                    std::cout << "BAD RET" << std::endl;
                    stack_delete(stack);
                    return 1;
                }
                stack_pop(stack);
                break;
            }

            case CommandType::INVALID: {
                std::cout << "Invalid command!" << std::endl;
                break;
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
