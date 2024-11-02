#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "stack.h"

using namespace std;

int main() {
    ifstream input(INPUT_FILE);  // Используем путь к input.txt
    ofstream output(OUTPUT_FILE);  // Используем путь к output.txt
    
    if (!input.is_open()) {
        cerr << "Error opening input file!" << endl;
        return 1;
    }
    if (!output.is_open()) {
        cerr << "Error opening output file!" << endl;
        return 1;
    }

    string line;
    while (getline(input, line)) {
        Stack stack;
        istringstream tokens(line);
        string token;
        bool error = false;

        while (tokens >> token) {
            if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
                stack.push(stoi(token));
            } else if (token == "+" || token == "-" || token == "*" || token == "/") {
                if (stack.empty()) {
                    output << "UNDERFLOW" << endl;
                    error = true;
                    break;
                }
                int b = stack.get();
                stack.pop();

                if (stack.empty()) {
                    output << "UNDERFLOW" << endl;
                    error = true;
                    break;
                }
                int a = stack.get();
                stack.pop();

                if (token == "+") stack.push(a + b);
                else if (token == "-") stack.push(a - b);
                else if (token == "*") stack.push(a * b);
                else if (token == "/") {
                    if (b == 0) {
                        output << "ZERO" << endl;
                        error = true;
                        break;
                    }
                    stack.push(a / b);
                }
            } else {
                output << "Invalid token: " << token << endl;
                error = true;
                break;
            }
        }

        if (!error) {
            if (stack.empty()) {
                output << "UNDERFLOW" << endl;
            } else if (stack.get() == 0) {
                output << stack.get() << endl; // Если результат равен нулю, выводим его
            } else if (!stack.empty()) {
                int result = stack.get();
                stack.pop();
                
                if (!stack.empty()) {
                    output << "OVERFLOW" << endl; // Если после извлечения остается элемент
                } else {
                    output << result << endl; // Если остался единственный элемент, выводим его
                }
            }
        }
    }

    input.close();
    output.close();
    return 0;
}
