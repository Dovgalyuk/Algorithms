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
    while (getline(input, line)) { // ������ ������ ������ � ���������� � �������� �������� ������
        Stack stack;
        istringstream tokens(line); // ����� ��� ������� ������ �� ������
        string token;
        bool error = false; // ���� ��� ������������ ������ � ���������

        while (tokens >> token) { // ������ ������� ������
            if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
                // ���� ����� � �����, ����������� ��� � int � ��������� � ����
                stack.push(stoi(token));
            }
            else if (token == "+" || token == "-" || token == "*" || token == "/") {
                // ���� ����� � ��������, ��������� ������� ���� �� ���� ��������� � �����
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

                // ���������� ��������������� �������� � ���������� ���������� � ����
                if (token == "+") stack.push(a + b);
                else if (token == "-") stack.push(a - b);
                else if (token == "*") stack.push(a * b);
                else if (token == "/") {
                    // �������� ������� �� ����
                    if (b == 0) {
                        output << "ZERO" << endl;
                        error = true;
                        break;
                    }
                    stack.push(a / b);
                }
            }
            else {
                // ���� ����� �� ��������� ��� ����� ��� ��������
                output << "Invalid token: " << token << endl;
                error = true;
                break;
            }
        }

        if (!error) {
            // �������� ��������� ��������� �����: ���� ������� � ���������� ���������, ������ � OVERFLOW, ��� � UNDERFLOW
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
