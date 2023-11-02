#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <sstream>
#include <unordered_map>

using namespace std;

void main() {
    string filename = "input.txt";
    Stack* stack = stack_create();
    unordered_map<char, int> registers = { {'A', 0}, {'B', 0}, {'C', 0}, {'D', 0} };

    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Failed to open input file." << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        char param;
        int value;

        if (line.empty()) {
            continue;
        }

        if (line.substr(0, 4) == "PUSH") {
            stringstream ss(line.substr(5));
            if (isalpha(ss.peek())) {
                ss >> param;
                value = registers[param];
            }
            else {
                ss >> value;
            }
            stack_push(stack, value);
        }
        else if (line.substr(0, 3) == "POP") {
            stringstream ss(line.substr(4));
            ss >> param;
            value = stack_get(stack);
            stack_pop(stack);
            registers[param] = value;
        }
        else {
            cerr << "Invalid operation: " << line << endl;
            return;
        }
    }

    inputFile.close();
    stack_delete(stack);

    for (std::pair<char, int> element : registers) cout << element.first << " = " << element.second << endl;
}
