#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "stack.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);

    if (!input.is_open() || !output.is_open()) {
        cerr << "Error opening input or output file!" << endl;
        return 1;
    }

    string line;
    while (getline(input, line)) { // Чтение каждой строки с выражением в обратной польской записи
        Stack stack;
        istringstream tokens(line); // Поток для разбора строки на токены
        string token;
        bool error = false; // Флаг для отслеживания ошибок в выражении

        while (tokens >> token) { // Чтение каждого токена
            if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
                // Если токен — число, преобразуем его в int и добавляем в стек
                stack.push(stoi(token));
            }
            else if (token == "+" || token == "-" || token == "*" || token == "/") {
                // Если токен — оператор, проверяем наличие хотя бы двух элементов в стеке
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

                // Выполнение соответствующей операции и добавление результата в стек
                if (token == "+") stack.push(a + b);
                else if (token == "-") stack.push(a - b);
                else if (token == "*") stack.push(a * b);
                else if (token == "/") {
                    // Проверка деления на ноль
                    if (b == 0) {
                        output << "ZERO" << endl;
                        error = true;
                        break;
                    }
                    stack.push(a / b);
                }
            }
            else {
                // Если токен не распознан как число или оператор
                output << "Invalid token: " << token << endl;
                error = true;
                break;
            }
        }

        if (!error) {
            // Проверка конечного состояния стека: один элемент — корректный результат, больше — OVERFLOW, нет — UNDERFLOW
            if (stack.empty()) {
                output << "UNDERFLOW" << endl;
            }
            else if (!stack.empty() && stack.get() != 0) {
                output << "OVERFLOW" << endl;
            }
            else {
                output << stack.get() << endl;
            }
        }
    }

    input.close();
    output.close();
    return 0;
}
