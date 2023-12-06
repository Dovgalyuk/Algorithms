#include <iostream>
#include <fstream>
#include <string>

bool isTagOpening(const std::string& tag) {
    return tag[0] == '<' && tag[1] != '/';
}

bool isTagClosing(const std::string& tag) {
    return tag[0] == '<' && tag[1] == '/';
}

int main() {
    std::ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }

    std::ofstream outputFile("output.txt");

    if (!outputFile.is_open()) {
        stdcerr << "Error opening output file" << std::endl;
        return 1;
    }

    Stack* stack = stack_create();
    std::string tag;

    while (std::getline(inputFile, tag)) {
        if (isTagOpening(tag)) {
            stack_push(stack, tag);
        } else if (isTagClosing(tag)) {
            if (stack_empty(stack)) {
                outputFile << "NO" << std::endl;
                return 0;
            }
            std::string topTag = stack_get(stack);
            if (topTag.substr(1) != tag.substr(2)) {
                outputFile << "NO" << std::endl;
                return 0;
            }
            stack_pop(stack);
        }
    }

    if (stack_empty(stack)) {
        outputFile << "YES" << std::endl;
    } else {
        outputFile << "NO" << std::endl;
    }

    stack_delete(stack);
    inputFile.close();
    outputFile.close();

    return 0;
}