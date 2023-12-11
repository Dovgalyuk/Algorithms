#include <iostream>
#include <fstream>
#include "stack.h"
#include <string>
#include <unordered_map>

bool checkTags(const std::string& inputFile, const std::string& outputFile) {
    Stack* tagStack = stack_create();

    std::ifstream inFile(inputFile);
    if (!inFile) {
        std::cout << "Failed to open input file." << std::endl;
        return false;
    }

    std::string tag;
    std::hash<std::string> hasher;
    while (std::getline(inFile, tag)) {
        if (tag.empty()) {
            continue;
        }
        for (size_t i = 0; i < tag.size(); i++) {
            tag[i] = tolower(tag[i]);
        }

        if (tag[0] == '<' && tag[tag.size() - 1] == '>') {
            if (tag[1] == '/') {
                if (stack_empty(tagStack)) {
                    std::ofstream outFile(outputFile);
                    outFile << "NO";
                    return false;
                }

                std::string openTag = std::to_string(stack_get(tagStack));
                stack_pop(tagStack);

                std::string closeTag = std::to_string(hasher(tag.substr(2, tag.size() - 3)));
                if (openTag != closeTag) {
                    std::ofstream outFile(outputFile);
                    outFile << "NO";
                    return false;
                }
            }
            else {
                size_t tagInfo = hasher(tag.substr(1, tag.size() - 2));
                stack_push(tagStack, tagInfo);
            }
        }
    }

    if (stack_empty(tagStack)) {
        std::ofstream outFile(outputFile);
        outFile << "YES";
        return true;
    }
    else {
        std::ofstream outFile(outputFile);
        outFile << "NO";
        return false;
    }
    stack_delete(tagStack);
}

int main() { 
    std::string inputFile = "inputl2.txt";
    std::string outputFile = "outputl2.txt";

    if (checkTags(inputFile, outputFile)) {
        std::cout << "Tags are correct." << std::endl;
    }
    else {
        std::cout << "Tags are incorrect." << std::endl;
    }

    return 0;
}
