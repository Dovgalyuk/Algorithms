#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

using namespace std;

bool is_valid_sequence(const string& sequence) {
    Stack* stack = stack_create();
    
    for (char c : sequence) {
        switch (c) {
            case '(':
            case '[':
            case '{':
                stack_push(stack, c);
                break;
                
            case ')':
                if (stack_empty(stack) || stack_get(stack) != '(') {
                    stack_delete(stack);
                    return false;
                }
                stack_pop(stack);
                break;
                
            case ']':
                if (stack_empty(stack) || stack_get(stack) != '[') {
                    stack_delete(stack);
                    return false;
                }
                stack_pop(stack);
                break;
                
            case '}':
                if (stack_empty(stack) || stack_get(stack) != '{') {
                    stack_delete(stack);
                    return false;
                }
                stack_pop(stack);
                break;
                
            case '\"':
                // Обработка кавычек
                if (!stack_empty(stack) && stack_get(stack) == '\"') {
                    stack_pop(stack);
                } else {
                    stack_push(stack, '\"');
                }
                break;
                
            case '\'':
                // Обработка апострофов
                if (!stack_empty(stack) && stack_get(stack) == '\'') {
                    stack_pop(stack);
                } else {
                    stack_push(stack, '\'');
                }
                break;
        }
    }
    
    bool result = stack_empty(stack);
    stack_delete(stack);
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }
    
    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        cerr << "Error opening input file: " << argv[1] << endl;
        return 1;
    }
    
    ofstream outputFile(argv[2]);
    if (!outputFile.is_open()) {
        cerr << "Error opening output file: " << argv[2] << endl;
        inputFile.close();
        return 1;
    }
    
    string sequence;
    getline(inputFile, sequence);
    
    if (is_valid_sequence(sequence)) {
        outputFile << "YES";
    } else {
        outputFile << "NO";
    }
    
    inputFile.close();
    outputFile.close();
    return 0;
}