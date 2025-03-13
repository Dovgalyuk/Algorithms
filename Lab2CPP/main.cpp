#include <iostream>
#include <stack>
#include <string>

bool is_balanced(const std::string& str) {
    std::stack<char> stack;
    
    for (char ch : str) {
        if (ch == '(' || ch == '[' || ch == '{' || ch == '"' || ch == '\'') {  // Заменил на кавычки
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
    std::string expression = "{[()]}";
    if (is_balanced(expression)) {
        std::cout << "Balanced\n";
    } else {
        std::cout << "Not Balanced\n";
    }
    return 0;
}
