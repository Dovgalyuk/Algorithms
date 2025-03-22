#include <iostream>
#include <stack>
#include <string>

bool is_balanced(const std::string& str) {
    std::stack<char> stack;
    
    for (char ch : str) {
        if (ch == '(' || ch == '[' || ch == '{' || ch == '"' || ch == '\'') {
            stack.push(ch);
        } else if (ch == ')' || ch == ']' || ch == '}' || ch == '"' || ch == '\'') {
            if (stack.empty()) return false;
            char top = stack.top();
            stack.pop();
            if ((ch == ')' && top != '(') || 
                (ch == ']' && top != '[') || 
                (ch == '}' && top != '{') || 
                (ch == '"' && top != '"') || 
                (ch == '\'' && top != '\'')) {
                return false;
            }
        }
    }
    
    return stack.empty();
}

int main() {
    std::string input;
    
    std::cout << "Enter the line to check: ";
    std::getline(std::cin, input);
    
    if (is_balanced(input)) {
        std::cout << "YES\n"; 
    } else {
        std::cout << "NO\n"; 
    }
    
    return 0;
}
