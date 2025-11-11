#include "Lab2.h"
#include "vector.h"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
	if (argc != 3) {
		std::cerr << "Programm need 3 argument";
		std::exit(1);
	}

	std::ifstream scriptFile(argv[1]);
	if (!scriptFile) {
		std::cerr << "Failed to open script file";
		std::exit(1);
	}

	std::string script((std::istreambuf_iterator<char>(scriptFile)), std::istreambuf_iterator<char>());
	auto scores = tokenize(script);

	std::ifstream inputFile(argv[2], std::ios::binary);
	if (!inputFile) {
		std::cerr << "Failed to open input file";
		std::exit(1);
	}

	run(scores, inputFile, std::cout);

	return 0;
}
