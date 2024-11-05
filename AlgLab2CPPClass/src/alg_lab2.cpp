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

        input = &inputFile;
        output = &outputFile;
    }

    menu();

    if (inputFile.is_open()) inputFile.close();
    if (outputFile.is_open()) outputFile.close();

    return 0;
}

void task1() {
    std::string input = "123...";
    Interpreter interpreter;
    interpreter.run(input);
}

void task2() {
    std::string input = "1:.2:.3:.++.";
    Interpreter interpreter;
    interpreter.run(input);
}

void task3() {
    std::string input = "9!.";
    Interpreter interpreter;
    interpreter.run(input);
}

void task4() {
    std::string input = "5 3`.";
    Interpreter interpreter;
    interpreter.run(input);
}

void task5() {
    std::string input = "34*.";
    Interpreter interpreter;
    interpreter.run(input);
}

void own_task() {
    std::string input;
    std::cout << "Enter Befunge commands:";
    std::cin >> input;
    Interpreter interpreter;
    interpreter.run(input);
}

void menu() {
    int menu_num = 0;
    *output << "-- [ Befunge Interpreter ] --\n";
    *output << "0. Manual entry\n";
    *output << "1. Task 1\n";
    *output << "2. Task 2\n";
    *output << "3. Task 3\n";
    *output << "4. Task 4\n";
    *output << "5. Task 5\n";
    *output << "Choose an option:";

    std::cin >> menu_num;

    switch (menu_num) {
        case 0: own_task(); break;
        case 1: task1(); break;
        case 2: task2(); break;
        case 3: task3(); break;
        case 4: task4(); break;
        case 5: task5(); break;
        default:
            std::cerr << "Invalid input!\n";
            break;
    }
}
