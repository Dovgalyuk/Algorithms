#include <iostream> 
#include <fstream> 
#include <string> 
#include "stack.h" 
 
bool isMatchingPair(char opening, char closing) { 
    if (opening == '(' && closing == ')') { 
        return true; 
    } 
    if (opening == '"' && closing == '"') { 
        return true; 
    } 
    return false; 
} 
 
bool is_balanced(const std::string& str) {
    Stack* stack = stack_create();
    bool is_quote_open = false;

    for (char c : str) {
        if (c == '"') {
            is_quote_open = !is_quote_open;
        } else if (!is_quote_open) {
            if (c == '(') {
                stack_push(stack, static_cast<Data>(c));
            } else if (c == ')') {
                if (stack_empty(stack) || stack_get(stack) != '(') {
                    stack_delete(stack);
                    return false; 
                }
                stack_pop(stack);
            }
        }
    }  

    bool balanced = stack_empty(stack) && !is_quote_open;
    stack_delete(stack); 
    return balanced;
}

 
int main(int argc, char **argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input.txt> <output.txt>\n";
        return 1;
    }

    std::ifstream infile(argv[1]);
    std::ofstream outfile(argv[2]);
    std::string s;

    while (std::getline(infile, s)) {
        if (is_balanced(s)) {
            outfile << "YES" << std::endl;
        } else {
            outfile << "NO" << std::endl;
        }
    }

    return 0;
}