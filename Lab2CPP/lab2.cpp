#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

int command_to_num(const std::string& cmd) {
    if (cmd == "add") return 1;
    if (cmd == "sub") return 2;
    if (cmd == "mul") return 3;
    if (cmd == "div") return 4;
    if (cmd == "sqrt") return 5;
    if (cmd == "sq") return 6;
    if (cmd == "get") return 7;
    if (cmd == "peek") return 8;
    if (cmd == "cond") return 9;
    if (cmd == "end") return 10;
    if (cmd == "setr") return 11;
    if (cmd == "repeat") return 12;
    return 0;
}

void read_commands_stack_from_file(const char* filename, Stack* cmds) {
    std::ifstream file(filename);
    std::string cmd;
    while (file >> cmd) {
        int code = command_to_num(cmd);
        stack_push(cmds, code);
    }
}

void read_numbers_stack_from_file(const char* filename, Stack* nums) {
    Stack* temp = stack_create();
    std::ifstream file(filename);
    int num;

    while (file >> num) {
        stack_push(temp, num);
    }

    while (!stack_empty(temp)) {
        Data val = stack_get(temp);
        stack_pop(temp);
        stack_push(nums, val);
    }
    stack_delete(temp);
}

void reverse_stack(Stack* stack) {
    Stack* temp = stack_create();
    while (!stack_empty(stack)) {
        Data val = stack_get(stack);
        stack_pop(stack);
        stack_push(temp, val);
    }
    while (!stack_empty(temp)) {
        Data val = stack_get(temp);
        stack_pop(temp);
        stack_push(stack, val);
    }
    stack_delete(temp);
}

int main(int argc, char* argv[]) {
    const char* num_file = argc > 1 ? argv[1] : "input.txt";
    const char* cmd_file = argc > 2 ? argv[2] : "input_commands.txt";

    Stack* nums = stack_create();
    Stack* cmds = stack_create();
    Stack* res = stack_create();

    read_numbers_stack_from_file(num_file, nums);
    read_commands_stack_from_file(cmd_file, cmds);
    reverse_stack(cmds);

    while (!stack_empty(cmds)) {
        int cmd = stack_get(cmds);
        stack_pop(cmds);

        switch (cmd) {
        case 8:  // peek 

            break;
        case 11: // setr 
            if (!stack_empty(nums)) {
                Data val = stack_get(nums);
                stack_pop(nums);
                stack_push(res, val);
            }
            break;
        default:

            break;
        }
    }

    reverse_stack(res);

    while (!stack_empty(res)) {
        Data val = stack_get(res);
        stack_pop(res);
        std::cout << val << " ";
    }
    std::cout << std::endl;

    stack_delete(nums);
    stack_delete(cmds);
    stack_delete(res);

    return 0;
}








