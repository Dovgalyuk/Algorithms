#include <iostream>
#include <fstream>
#include "stack.h"

bool checkHTMLSequence(std::ifstream &inputFile) {
    Stack* tagStack = stack_create();
    std::string tag;
    while (std::getline(inputFile, tag)) {
        if (tag.find("</") == 0) {
            Data openTag;
            if (!stack_empty(tagStack)) {
                openTag = stack_get(tagStack);
                stack_pop(tagStack);
                std::string openTagString = "<" + openTag + ">";
                if (openTagString != tag) {
                    stack_delete(tagStack);
                    return false;
                }
            } else {
                stack_delete(tagStack);
                return false;
            }
        } else {
            tag = tag.substr(1, tag.length() - 2);
            stack_push(tagStack, tag);
        }
    }
    bool result = stack_empty(tagStack);
    stack_delete(tagStack);
    return result;
}

int main() {
    std::ifstream inputFile("input.txt");
    if (inputFile.is_open()) {
        if (checkHTMLSequence(inputFile)) {
            std::cout << "YES" << std::endl;
        } else {
            std::cout << "NO" << std::endl;
        }
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }
    inputFile.close();
    return 0;
}
