#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <stack.h>
#include <list.h>

enum class Commands { PUSH, POP, CALL, RET, ERROR };

struct Command {
	Commands type;
	int value;
};

Command parseCommand(std::string& str) {
	Command command = { Commands::ERROR, 0 };
	std::istringstream iss(str);
	std::string operation;
	iss >> operation;

	if (operation == "push") {
		command.type = Commands::PUSH;
		std::string typeValue;
		iss >> typeValue;

		if (isalpha(typeValue[0])) {
			command.value = typeValue[0];
		}
		else {
			command.value = std::stoi(typeValue);
		}
	}
	else if (operation == "pop") {
		command.type = Commands::POP;
		std::string reg;
		iss >> reg;
		command.value = reg[0];
	}
	else if (operation == "call") {
		command.type = Commands::CALL;
	}
	else if (operation == "ret") {
		command.type = Commands::RET;
	}
	return command;
}



int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
		return 1;
	}

	std::string filename = argv[1];
	Stack* stack = stack_create();
	std::map<char, int> registers = { {'A', 0}, {'B', 0}, {'C', 0}, {'D', 0} };
	const int mark = -1;


	std::string str;
	std::ifstream inputFile(filename);
	if (!inputFile.is_open()) {
		std::cout << "File not found" << std::endl;
		stack_delete(stack);
		return 1;
	}
	while (std::getline(inputFile, str)) {
		Command command = parseCommand(str);

		switch (command.type) {
		case Commands::PUSH: {
			char check = static_cast<char>(command.value);
			if (check == 'A' || check == 'B' || check == 'C' || check == 'D') {
				if (check == 'A') stack_push(stack, registers['A']);
				if (check == 'B') stack_push(stack, registers['B']);
				if (check == 'C') stack_push(stack, registers['C']);
				if (check == 'D') stack_push(stack, registers['D']);
			}
			else {
				stack_push(stack, command.value);
			}
			break;
		}
		case Commands::POP: {
			if (stack_empty(stack) || stack_get(stack) == mark) {
				std::cout << "BAD POP" << std::endl;
				inputFile.close();
				stack_delete(stack);
				return 1;
			}
			int value = stack_get(stack);
			registers[static_cast<char>(command.value)] = value;
			stack_pop(stack);
			break;
		}
		case Commands::CALL: {
			stack_push(stack, mark);
			break;
		}
		case Commands::RET: {
			if (stack_empty(stack) || stack_get(stack) != mark) {
				std::cout << "BAD RET" << std::endl;
				inputFile.close();
				stack_delete(stack);
				return 1;
			}
			stack_pop(stack);
			break;
		}
		case Commands::ERROR: {
			std::cout << "BAD COMMAND" << std::endl;
			inputFile.close();
			stack_delete(stack);
			break;
		}
		}
	}

	for (auto& pair : registers) {
		std::cout << pair.first << " = " << pair.second << std::endl;
	}
	inputFile.close();
	stack_delete(stack);

	return 0;
}