#include <iostream>
#include <fstream>
#include "stack.h"
using namespace std;
bool checkHtmlTags(const string& inputFile, const string& outputFile) {
    Stack *stack = stack_create();
    
    ifstream file(inputFile);
    if (!file) {
        cout << "Failed." << endl;
        stack_delete(stack);
        return false;
    }
    
    string line;
    while (getline(file, line)) {
        string tag = line;
        if (tag.find("</") == 0) {
            if (stack_empty(stack)) {
                ofstream outFile(outputFile);
                outFile << "NO";
                outFile.close();
                stack_delete(stack);
                return true;
            }
            string openTag = stack_get(stack);
            string closeTag = tag.substr(2, tag.length() - 3);
            if (openTag != closeTag) {
                ofstream outFile(outputFile);
                outFile << "NO";
                outFile.close();
                stack_delete(stack);
                return true;
            }
            stack_pop(stack);
        } else {
            stack_push(stack, tag.substr(1, tag.length() - 2));
        }
    }
    
    if (stack_empty(stack)) {
        ofstream outFile(outputFile);
        outFile << "YES";
        outFile.close();
    } else {
        ofstream outFile(outputFile);
        outFile << "NO";
        outFile.close();
    }
    
    stack_delete(stack);
    
    return true;
}

int main() {
    checkHtmlTags("input.txt", "output.txt");
    
    return 0;
}