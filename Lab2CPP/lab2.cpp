#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include "array.h"
#include "stack.h"

std::ifstream inputnum("inputnum");

enum Command {
    cmd_none = 0,
    cmd_add = 1,
    cmd_sub = 2,
    cmd_mul = 3,
    cmd_div = 4,
    cmd_sqrt = 5,
    cmd_sq = 6,
    cmd_get = 7,
    cmd_peek = 8,
    cmd_cond = 9,
    cmd_end = 10,
    cmd_setr = 11,
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

void read_numbers_and_commands_from_file(const char* filename, Stack* nums, Array* cmds_array, size_t& cmds_count) {
    std::ifstream file(filename);
    std::string token;
    bool reading_commands = false;

    const size_t max_cmds = array_size(cmds_array);
    cmds_count = 0;

    while (file >> token) {
        if (!reading_commands) {
            try {
                int num = std::stoi(token);
                stack_push(nums, num);
            }
            catch (...) {
                reading_commands = true;
            }
        }
        if (reading_commands) {
            Command cmd_code = command_to_num(token);
            if (cmd_code != cmd_none && cmds_count < max_cmds) {
                array_set(cmds_array, cmds_count, static_cast<Data>(cmd_code));
                cmds_count++;
            }
        }
    }
}

void execute_commands(Array* cmds, size_t count, Stack* nums) {
    int loop_var = 0;
    size_t i = 0;

    while (i < count) {
        Command cmd = static_cast<Command>(array_get(cmds, i));

        switch (cmd) {
        case cmd_peek:
            if (!stack_empty(nums)) {
                Data val = stack_get(nums);
                std::cout << val << " ";
            }
            ++i;
            break;

        case cmd_setr:
            if (!stack_empty(nums)) {
                loop_var = stack_get(nums);
                stack_pop(nums);
            }
            ++i;
            break;

        case cmd_add:
            if (!stack_empty(nums)) {
                int a = stack_get(nums);
                stack_pop(nums);
                if (!stack_empty(nums)) {
                    int b = stack_get(nums);
                    stack_pop(nums);
                    stack_push(nums, a + b);
                }
            }
            ++i;
            break;

        case cmd_sub:
            if (!stack_empty(nums)) {
                int a = stack_get(nums);
                stack_pop(nums);
                if (!stack_empty(nums)) {
                    int b = stack_get(nums);
                    stack_pop(nums);
                    stack_push(nums, b - a);
                }
            }
            ++i;
            break;

        case cmd_mul:
            if (!stack_empty(nums)) {
                int a = stack_get(nums);
                stack_pop(nums);
                if (!stack_empty(nums)) {
                    int b = stack_get(nums);
                    stack_pop(nums);
                    stack_push(nums, a * b);
                }
            }
            ++i;
            break;

        case cmd_div:
            if (!stack_empty(nums)) {
                int a = stack_get(nums);
                stack_pop(nums);
                if (!stack_empty(nums) && a != 0) {
                    int b = stack_get(nums);
                    stack_pop(nums);
                    stack_push(nums, b / a);
                }
            }
            ++i;
            break;

        case cmd_sqrt:
            if (!stack_empty(nums)) {
                int a = stack_get(nums);
                stack_pop(nums);
                stack_push(nums, (int)sqrt(a));
            }
            ++i;
            break;

        case cmd_sq:
            if (!stack_empty(nums)) {
                int a = stack_get(nums);
                stack_pop(nums);
                stack_push(nums, a * a);
            }
            ++i;
            break;

        case cmd_get: {
            int val;
            if (inputnum >> val) {
                stack_push(nums, val);
            }
            else {
                return;
            }
            ++i;
            break;
        }

        case cmd_cond: {
            if (!stack_empty(nums)) {
                int a = stack_get(nums);
                stack_pop(nums);
                if (!stack_empty(nums)) {
                    int b = stack_get(nums);
                    stack_pop(nums);
                    if (a == b) {
                        ++i;
                    }
                    else {
                        size_t nested = 0;
                        do {
                            ++i;
                            if (i >= count) break;
                            Command cur = static_cast<Command>(array_get(cmds, i));
                            if (cur == cmd_cond) nested++;
                            if (cur == cmd_end) {
                                if (nested == 0) break;
                                else nested--;
                            }
                        } while (true);
                        ++i;
                    }
                }
                else {
                    size_t nested = 0;
                    do {
                        ++i;
                        if (i >= count) break;
                        Command cur = static_cast<Command>(array_get(cmds, i));
                        if (cur == cmd_cond) nested++;
                        if (cur == cmd_end) {
                            if (nested == 0) break;
                            else nested--;
                        }
                    } while (true);
                    ++i;
                }
            }
            else {
                size_t nested = 0;
                do {
                    ++i;
                    if (i >= count) break;
                    Command cur = static_cast<Command>(array_get(cmds, i));
                    if (cur == cmd_cond) nested++;
                    if (cur == cmd_end) {
                        if (nested == 0) break;
                        else nested--;
                    }
                } while (true);
                ++i;
            }
            break;
        }

        case cmd_end:
            ++i;
            break;

        case cmd_repeat:
            if (loop_var > 0) {
                loop_var--;
                ssize_t j = i - 1;
                while (j >= 0) {
                    Command c = static_cast<Command>(array_get(cmds, j));
                    if (c == cmd_setr)
                        break;
                    j--;
                }
                if (j >= 0) {
                    i = j + 1;
                }
                else {
                    ++i;
                }
            }
            else {
                ++i;
            }
            break;

        default:
            ++i;
            break;
        }
    }
}

int main(int argc, char* argv[]) {
  
    const char* input_files[3] = {
        argc > 1 ? argv[1] : "input.txt",
        argc > 2 ? argv[2] : "input2.txt",
        argc > 3 ? argv[3] : "input3.txt"
    };

    for (int t = 0; t < 3; ++t) {
        Stack* nums = stack_create();
        Array* cmds = array_create(64);
        size_t cmds_count = 0;

        read_numbers_and_commands_from_file(input_files[t], nums, cmds, cmds_count);

        execute_commands(cmds, cmds_count, nums);

        stack_delete(nums);
        array_delete(cmds);
    }

    inputnum.close();
    return 0;
}












