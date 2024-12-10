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
    bool is_quote_open = false; // для отслеживания кавычек

    for (char c : str) {
        if (c == '"') {
            is_quote_open = !is_quote_open; // переключаем состояние кавычки
        } else if (!is_quote_open) { // если не в кавычках, обрабатываем скобки
            if (c == '(') {
                stack_push(stack, static_cast<Data>(c));
            } else if (c == ')') {
                if (stack_empty(stack)) {
                    stack_delete(stack);
                    return false; // лишняя закрывающая скобка
                }
                Data top = stack_get(stack);
                stack_pop(stack);
                if (top != '(') {
                    stack_delete(stack);
                    return false; // несоответствие скобок
                }
            }
        }
    }

    // проверка
    bool balanced = stack_empty(stack) && !is_quote_open;
    stack_delete(stack); 
    return balanced;
}

int main() { 
    std::ifstream infile("input.txt"); 
    std::ofstream outfile("output.txt"); 
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