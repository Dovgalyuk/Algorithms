#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <sstream>
#include <stack.h>
#include <list.h>

enum class Commands { PUSH, POP, CALL, RET, ERROR };

struct Command {
	Commands type;
	int value;
	std::string rg;
};

Command parseCommand(std::string& str) {
	Command command = { Commands::ERROR, 0, "default" };
	std::istringstream iss(str);
	std::string operation;
	iss >> operation;

	if (operation == "push") {
		command.type = Commands::PUSH;
		std::string typeValue;
		iss >> typeValue;

		command.rg = typeValue;

		/*if (std::all_of(typeValue.begin(), typeValue.end(), [](char c) { return std::isdigit(c) != 0; })) {
				command.value = std::stoi(typeValue);
		}
		else {
			command.type = Commands::ERROR;
		}*/
	}
	else if (operation == "pop") {
		command.type = Commands::POP;
		std::string reg;
		iss >> reg;
		if (reg != "A" && reg != "B" && reg != "C" && reg != "D") {
			command.type = Commands::ERROR;
		}
		else {
			command.value = reg[0];
		}
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
	std::map<char, int> registers = { {'A', 0}, {'B', 0}, {'C', 0}, {'D', 0}};
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
		std::string rg;

		switch (command.type) {
		case Commands::PUSH: {
			//char check = static_cast<char>(command.value);
			if (command.rg == "A") stack_push(stack, registers['A']);
			else if (command.rg == "B") stack_push(stack, registers['B']);
			else if (command.rg == "C") stack_push(stack, registers['C']);
			else if (command.rg == "D") stack_push(stack, registers['D']);

			else if (std::all_of(command.rg.begin(), command.rg.end(), [](char c) { return std::isdigit(c) != 0; })) {
				command.value = std::stoi(command.rg);
				stack_push(stack, command.value);
			}
			else {
				std::cout << "BAD PUSH" << std::endl;
				inputFile.close();
				stack_delete(stack);
				return 1;
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
			std::cout << "BAD COMMAND OR BAD DATA" << std::endl;
			inputFile.close();
			stack_delete(stack);
			return 1;
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