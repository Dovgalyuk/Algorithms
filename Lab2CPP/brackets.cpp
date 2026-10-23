#include "stack.h"
#include <iostream>
#include <fstream>
#include <string>

static bool isMatchcingPair(char open, char close)
{
	return (open == '(' && close == ')')
		|| (open == '[' && close == ']')
		|| (open == '{' && close == '}')
		|| (open == '<' && close == '>');
}

static bool isOpening(char c)
{
	return c == '(' || c == '[' || c == '{' || c == '<';
}

static bool isClosing(char c)
{
	return c == ')' || c == ']' || c == '}' || c == '>';
}

static bool checkBrackets(const std::string& line)
{
	Stack stack;

	for (char c : line) {
		if (isOpening(c)) {
			stack.push((Data)c);
		}
		else if (isClosing(c)) {
			if (stack.empty()) {
				return false;
			}
			
			char top = (char)stack.get();
			if (!isMatchcingPair(top, c)) {
				return false;
			}

			stack.pop();
		}
	}

	return stack.empty();
}

int main(int argc, char* argv[])
{
	if (argc < 3) {
		std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
		return 1;
	}

	std::ifstream infile(argv[1]);
	if (!infile.is_open()) {
		std::cerr << "Cannot open input file" << argv[1] << std::endl;
		return 1;
	}

	std::string line;
	std::getline(infile, line);

	std::ofstream outfile(argv[2]);
	if (!outfile.is_open()) {
		std::cerr << "Cannot open output file" << argv[2] << std::endl;
		return 1;
	}

	if (line.empty()) {
		outfile << "NO" << std::endl;
		return 0;
	}

	bool result = checkBrackets(line);
	outfile << (result ? "YES" : "NO") << std::endl;

	return 0;
}