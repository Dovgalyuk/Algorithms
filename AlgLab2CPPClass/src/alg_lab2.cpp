#include <iostream>
#include "befunge_interpreter.h"
#include "alg_lab2.h"

int main(int argc, char* argv[]) {
    std::ifstream inputFile;
    std::ofstream outputFile;

    if (argc == 3) {
        inputFile.open(argv[1]);
        outputFile.open(argv[2]);

        if (!inputFile || !outputFile) {
            std::cerr << "Error opening file!\n";
            return 1;
        }

        menu(inputFile, outputFile);

        inputFile.close();
        outputFile.close();
    } else {
        menu(std::cin, std::cout);
    }

    return 0;
}

void own_task(std::istream& input, std::ostream& output) {
    std::string commands;

    input.ignore();
    std::getline(input, commands);

    Interpreter interpreter;
    interpreter.run(commands, output);
}

void menu(std::istream& input, std::ostream& output) {
    bool running = true;

    while (running) {
        int menu_num = -1;
        output << "\n-- [ Befunge Interpreter ] --\n";
        output << "0. Start Befunge\n";
        output << "1. Exit\n";
        input >> menu_num;

        switch (menu_num) {
            case 0: own_task(input, output); break;
            case 1: {
                output << "Exiting program.\n";
                running = false;
                break;
            }
            default:
                output << "Invalid input! Please try again.\nExiting program.\n";
                exit(1);
        }
    }
}
