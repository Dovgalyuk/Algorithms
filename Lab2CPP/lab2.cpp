#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include "stack.h"

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

void read_numbers_and_commands_from_file(const char* filename, Stack* nums, std::vector<Command>& cmds) {
	std::ifstream file(filename);
	std::string token;

	while (file >> token) {
		Command cmd_code = command_to_num(token);
		if (cmd_code != cmd_none) {
			cmds.push_back(cmd_code);
		}
		else {
			int num = std::stoi(token);
			stack_push(nums, num);

		}
	}
}


size_t skip_cond_block(const std::vector<Command>& cmds, size_t current_index, size_t count) {
	size_t nested = 0;
	size_t i = current_index + 1;
	while (i < count) {
		if (cmds[i] == cmd_cond) nested++;
		else if (cmds[i] == cmd_end) {
			if (nested == 0) break;
			nested--;
		}
		i++;
	}
	return i + 1;
}

void execute_commands(const std::vector<Command>& cmds, Stack* nums, std::ifstream& inputnum) {
	int loop_var = 0;
	size_t i = 0;
	size_t count = cmds.size();

	while (i < count) {
		Command cmd = cmds[i];

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
				int a = stack_get(nums); stack_pop(nums);
				if (!stack_empty(nums)) {
					int b = stack_get(nums); stack_pop(nums);
					stack_push(nums, a + b);
				}
			}
			++i;
			break;

		case cmd_sub:
			if (!stack_empty(nums)) {
				int a = stack_get(nums); stack_pop(nums);
				if (!stack_empty(nums)) {
					int b = stack_get(nums); stack_pop(nums);
					stack_push(nums, b - a);
				}
			}
			++i;
			break;

		case cmd_mul:
			if (!stack_empty(nums)) {
				int a = stack_get(nums); stack_pop(nums);
				if (!stack_empty(nums)) {
					int b = stack_get(nums); stack_pop(nums);
					stack_push(nums, a * b);
				}
			}
			++i;
			break;

		case cmd_div:
			if (!stack_empty(nums)) {
				int a = stack_get(nums); stack_pop(nums);
				if (!stack_empty(nums) && a != 0) {
					int b = stack_get(nums); stack_pop(nums);
					stack_push(nums, b / a);
				}
			}
			++i;
			break;

		case cmd_sqrt:
			if (!stack_empty(nums)) {
				int a = stack_get(nums); stack_pop(nums);
				stack_push(nums, (int)sqrt(a));
			}
			++i;
			break;

		case cmd_sq:
			if (!stack_empty(nums)) {
				int a = stack_get(nums); stack_pop(nums);
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
			if (stack_empty(nums)) {
				i = skip_cond_block(cmds, i, count);
				break;
			}
			int a = stack_get(nums); stack_pop(nums);
			if (stack_empty(nums)) {
				i = skip_cond_block(cmds, i, count);
				break;
			}
			int b = stack_get(nums); stack_pop(nums);

			if (a == b) {
				++i;
			}
			else {
				i = skip_cond_block(cmds, i, count);
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
				while (j >= 0 && cmds[j] != cmd_setr) j--;
				i = (j >= 0) ? j + 1 : i + 1;
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

	if (argc < 3) {
		return 1;
	}

	std::ifstream inputnum(argv[2]);
	if (!inputnum) {
		return 1;
	}

	Stack* nums = stack_create();
	std::vector<Command> cmds;

	read_numbers_and_commands_from_file(argv[1], nums, cmds);
	execute_commands(cmds, nums, inputnum);

	stack_delete(nums);
	inputnum.close();

	return 0;
}













