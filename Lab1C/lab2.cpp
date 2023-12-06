#include <fstream>
#include <iostream>
#include <string>
#include "list.h"
#include "stack.h"

bool checkTagSequence(const std::string& inputFileName, const std::string& outputFileName) {
    std::ifstream inputFile(inputFileName);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file" << std::endl;
        return false;
    }

    std::ofstream outputFile(outputFileName);

    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file" << std::endl;
        inputFile.close();
        return false;
    }

    Stack *stack = stack_create();
    std::string tag;

    while (std::getline(inputFile, tag)) {
        if (tag[0] == '<') {
            if (tag[1] == '/') {
                std::string topTag = stack_get(stack);
                if (topTag != tag.substr(2, tag.size() - 3)) {
                    outputFile << "NO" << std::endl;
                    inputFile.close();
                    outputFile.close();
                    stack_delete(stack);
                    return false;
                }
                stack_pop(stack);
            } else {
                stack_push(stack, tag);
            }
        }
    }

    bool correctSequence = stack_empty(stack);
    if (correctSequence) {
        outputFile << "YES" << std::endl;
    } else {
        outputFile << "NO" << std::endl;
    }

    stack_delete(stack);
    inputFile.close();
    outputFile.close();
    return true;
}

int main() {
    if (checkTagSequence("input.txt", "output.txt")) {
        std::cout << "Check complete, see output.txt for results." << std::endl;
    } else {
        std::cerr << "Tag sequence check failed." << std::endl;
    }
    return 0;
}