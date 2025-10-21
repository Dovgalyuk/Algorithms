#include <iostream>
#include <fstream>
#include <cmath> 
#include <string>
#include "stack.h"

enum Command {
    cmd_none = 0,
    cmd_add = 1, //done
    cmd_sub = 2, //done
    cmd_mul = 3, //done
    cmd_div = 4, //done
    cmd_sqrt = 5, //done
    cmd_sq = 6, //done
    cmd_get = 7, //done
    cmd_peek = 8, //done
    cmd_cond = 9,
    cmd_end = 10,
    cmd_setr = 11, //half done
    cmd_repeat = 12
};

Command command_to_num(const std::string& cmd) {
    if (cmd == "add") return cmd_add;
    if (cmd == "sub") return cmd_sub;
    if (cmd == "mul") return cmd_mul;
    if (cmd == "div") return cmd_div;
    if (cmd == "sqrt") return cmd_sqrt;
    if (cmd == "sq") return cmd_sq;
    if (cmd == "get") return cmd_get;
    if (cmd == "peek") return cmd_peek;
    if (cmd == "cond") return cmd_cond;
    if (cmd == "end") return cmd_end;
    if (cmd == "setr") return cmd_setr;
    if (cmd == "repeat") return cmd_repeat;
    return cmd_none;
}

void read_numbers_and_commands_from_file(const char* filename, Stack* nums, Stack* cmds) {
    std::ifstream file(filename);
    std::string token;
    bool reading_commands = false;

    while (file >> token) {
        if (!reading_commands) {
            try {
                int num = std::stoi(token);
                stack_push(nums, num);
            }
            catch (...) {
                reading_commands = true;
                Command cmd_code = command_to_num(token);
                if (cmd_code != cmd_none) {
                    stack_push(cmds, static_cast<Data>(cmd_code));
                }
            }
        }
        else {
            Command cmd_code = command_to_num(token);
            if (cmd_code != cmd_none) {
                stack_push(cmds, static_cast<Data>(cmd_code));
            }
        }
    }
}

Stack* copy_stack_with_reverse(Stack* original) {
    Stack* temp = stack_create();
    while (!stack_empty(original)) {
        stack_push(temp, stack_get(original));
        stack_pop(original);
    }
    return temp;
}

void execute_commands(Stack* temp_cmds, Stack* nums) {
    while (!stack_empty(temp_cmds)) {
        Command cmd = static_cast<Command>(stack_get(temp_cmds));
        stack_pop(temp_cmds);

        switch (cmd) {
        case cmd_peek:
            if (!stack_empty(nums)) {
                Data val = stack_get(nums);
                std::cout << val << " ";
            }
            break;
        case cmd_setr:
            if (!stack_empty(nums)) {
                stack_pop(nums);
            }
            break;
        case cmd_add:
            if (!stack_empty(nums)) {
                int a = stack_get(nums); 
                stack_pop(nums);
                if (!stack_empty(nums)) {
                    int b = stack_get(nums); stack_pop(nums);
                    stack_push(nums, a + b);
                }
            }
            break;
        case cmd_sub:
            if (!stack_empty(nums)) {
                int a = stack_get(nums); 
                stack_pop(nums);
                if (!stack_empty(nums)) {
                    int b = stack_get(nums); stack_pop(nums);
                    stack_push(nums, b - a);
                }
            }
            break;
        case cmd_mul:
            if (!stack_empty(nums)) {
                int a = stack_get(nums); 
                stack_pop(nums);
                if (!stack_empty(nums)) {
                    int b = stack_get(nums); stack_pop(nums);
                    stack_push(nums, a * b);
                }
            }
            break;
        case cmd_div:
            if (!stack_empty(nums)) {
                int a = stack_get(nums);
                stack_pop(nums);
                if (!stack_empty(nums) && a != 0) {
                    int b = stack_get(nums); stack_pop(nums);
                    stack_push(nums, b / a);
                }
            }
            break;
        case cmd_sqrt:
            if (!stack_empty(nums)) {
                int a = stack_get(nums); 
                stack_pop(nums);
                stack_push(nums, (int)sqrt(a));
            }
            break;
        case cmd_sq:
            if (!stack_empty(nums)) {
                int a = stack_get(nums); 
                stack_pop(nums);
                stack_push(nums, a * a);
            }
            break;
        case cmd_get:
        {
            int val;
            std::cout << "Enter number: ";
            std::cin >> val;
            stack_push(nums, val);
        }
        break;
        default:
            break;
        }
    }
}

int main(int argc, char* argv[]) {
    const char* input_file = argc > 1 ? argv[1] : "input.txt";

    Stack* nums = stack_create();
    Stack* cmds = stack_create();

    read_numbers_and_commands_from_file(input_file, nums, cmds);

    Stack* temp_cmds = copy_stack_with_reverse(cmds);

    execute_commands(temp_cmds, nums);

    stack_delete(nums);
    stack_delete(cmds);
    stack_delete(temp_cmds);



    const char* input_file2 = argc > 1 ? argv[1] : "input2.txt";

    Stack* nums2 = stack_create();
    Stack* cmds2 = stack_create();

    read_numbers_and_commands_from_file(input_file2, nums2, cmds2);

    Stack* temp_cmds2 = copy_stack_with_reverse(cmds2);

    execute_commands(temp_cmds2, nums2);

    stack_delete(nums2);
    stack_delete(cmds2);
    stack_delete(temp_cmds2);


    return 0;
}










