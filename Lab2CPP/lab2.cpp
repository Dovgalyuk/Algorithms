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
    bool is_quote_open = false; // Булевская переменная для отслеживания кавычек

    for (char c : str) {
        if (c == '(') {
            stack_push(stack, static_cast<Data>(c));
        } else if (c == '"') {
            if (!is_quote_open) {
                // Если открывающая кавычка
                stack_push(stack, static_cast<Data>(c));
                is_quote_open = true; // Помечаем, что кавычка открыта
            } else {
                // Если закрывающая кавычка
                if (stack_empty(stack) || stack_get(stack) != '"') {
                    stack_delete(stack);
                    return false; // Несоответствие кавычек
                }
                stack_pop(stack);
                is_quote_open = false; // Кавычка закрыта
            }
        } else if (c == ')') {
            if (stack_empty(stack)) {
                stack_delete(stack);
                return false; // Лишняя закрывающая скобка
            }
            Data top = stack_get(stack);
            stack_pop(stack);
            if (top != '(') {
                stack_delete(stack);
                return false; // Несоответствие скобок
            }
        }
    }

    // Проверяем, что все скобки и кавычки сбалансированы
    bool is_balanced = stack_empty(stack) && !is_quote_open;
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