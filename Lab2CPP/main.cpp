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
    // Тест 1:
    std::string expression1 = "{[()]}";
    std::cout << "Test 1: " << (is_balanced(expression1) ? "Balanced" : "Not Balanced") << std::endl;

    // Тест 2:
    std::string expression2 = "{[(])}";
    std::cout << "Test 2: " << (is_balanced(expression2) ? "Balanced" : "Not Balanced") << std::endl;

    // Тест 3: 
    std::string expression3 = "{[\"(hello)\"]}";
    std::cout << "Test 3: " << (is_balanced(expression3) ? "Balanced" : "Not Balanced") << std::endl;

    // Тест 4: 
    std::string expression4 = "{[(])}[{()}]";
    std::cout << "Test 4: " << (is_balanced(expression4) ? "Balanced" : "Not Balanced") << std::endl;

    // Тест 5:
    std::string expression5 = "{[";
    std::cout << "Test 5: " << (is_balanced(expression5) ? "Balanced" : "Not Balanced") << std::endl;

    // Тест 6:
    std::string expression6 = "([)]";
    std::cout << "Test 6: " << (is_balanced(expression6) ? "Balanced" : "Not Balanced") << std::endl;

    return 0;
}
