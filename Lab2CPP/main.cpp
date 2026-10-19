#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "stack.h"

using namespace std;

typedef vector<string> CodeGrid;

Data pop(Stack* stack)
{
    if (stack_empty(stack)) {
        return 0;
    }
    Data val = stack_get(stack);
    stack_pop(stack);
    return val;
}

void reverseStack(Stack*& stack)
{
    Stack* newStack = stack_create();
    while (!stack_empty(stack)) {
        stack_push(newStack, pop(stack));
    }
    stack_delete(stack);
    stack = newStack;
}

int main(int argc, char* argv[])
{
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <script.fish> <input.txt>" << endl;
        return 1;
    }

    ifstream scriptFile(argv[1]);
    if (!scriptFile.is_open()) {
        cerr << "Error opening script file" << endl;
        return 1;
    }

    CodeGrid grid;
    string line;
    size_t maxWidth = 0;
    while (getline(scriptFile, line)) {
        if (line.size() > maxWidth) {
            maxWidth = line.size();
        }
        grid.push_back(line);
    }
    scriptFile.close();

    if (grid.empty() || maxWidth == 0) {
        return 0;
    }

    for (size_t i = 0; i < grid.size(); i++) {
        if (grid[i].size() < maxWidth) {
            grid[i].append(maxWidth - grid[i].size(), ' ');
        }
    }

    ifstream inputFile(argv[2]);
    Stack* stack = stack_create();

    int x = 0;
    int y = 0;
    int dx = 1;
    int dy = 0;
    bool stringMode = false;
    bool running = true;

    int height = (int)grid.size();
    int width = (int)maxWidth;

    while (running) {
        char cmd = grid[y][x];

        if (stringMode) {
            if (cmd == '"') {
                stringMode = false;
            }
            else {
                stack_push(stack, (Data)cmd);
            }
        }
        else {
            switch (cmd) {
            case '"':
                stringMode = true;
                break;

            case '>':
                dx = 1;
                dy = 0;
                break;
            case '<':
                dx = -1;
                dy = 0;
                break;
            case '^':
                dx = 0;
                dy = -1;
                break;
            case 'v':
                dx = 0;
                dy = 1;
                break;

            case '/': {
                int temp = dx;
                dx = -dy;
                dy = -temp;
                break;
            }
            case '\\': {
                int temp = dx;
                dx = dy;
                dy = temp;
                break;
            }

            case '+': {
                Data b = pop(stack);
                Data a = pop(stack);
                stack_push(stack, a + b);
                break;
            }
            case '-': {
                Data b = pop(stack);
                Data a = pop(stack);
                stack_push(stack, a - b);
                break;
            }
            case '*': {
                Data b = pop(stack);
                Data a = pop(stack);
                stack_push(stack, a * b);
                break;
            }
            case ',': {
                Data b = pop(stack);
                Data a = pop(stack);
                if (b != 0) {
                    stack_push(stack, a / b);
                }
                break;
            }
            case '%': {
                Data b = pop(stack);
                Data a = pop(stack);
                if (b != 0) {
                    stack_push(stack, a % b);
                }
                break;
            }
            case '=': {
                Data b = pop(stack);
                Data a = pop(stack);
                stack_push(stack, (a == b) ? 1 : 0);
                break;
            }
            case ')': {
                Data b = pop(stack);
                Data a = pop(stack);
                stack_push(stack, (a > b) ? 1 : 0);
                break;
            }

            case ':':
                if (!stack_empty(stack)) {
                    stack_push(stack, stack_get(stack));
                }
                break;
            case '~':
                if (!stack_empty(stack)) {
                    stack_pop(stack);
                }
                break;
            case '$':
                if (!stack_empty(stack)) {
                    Data a = pop(stack);
                    Data b = pop(stack);
                    stack_push(stack, a);
                    stack_push(stack, b);
                }
                break;
            case 'r':
                reverseStack(stack);
                break;
            case 'l':
                stack_push(stack, (Data)stack_size(stack));
                break;

            case 'o':
                if (!stack_empty(stack)) {
                    cout << (char)pop(stack);
                }
                break;
            case 'n':
                if (!stack_empty(stack)) {
                    cout << pop(stack);
                }
                break;
            case 'i': {
                char ch = 0;
                if (inputFile.is_open() && inputFile.get(ch)) {
                    stack_push(stack, (Data)ch);
                }
                else {
                    stack_push(stack, -1);
                }
                break;
            }

            case '!':
                x = (x + dx + width) % width;
                y = (y + dy + height) % height;
                break;
            case '?': {
                Data val = pop(stack);
                if (val == 0) {
                    x = (x + dx + width) % width;
                    y = (y + dy + height) % height;
                }
                break;
            }

            case ';':
                running = false;
                break;

            default:
                if (cmd >= '0' && cmd <= '9') {
                    stack_push(stack, cmd - '0');
                }
                else if (cmd >= 'a' && cmd <= 'f') {
                    stack_push(stack, 10 + (cmd - 'a'));
                }
                break;
            }
        }

        x = (x + dx + width) % width;
        y = (y + dy + height) % height;
    }

    if (inputFile.is_open()) {
        inputFile.close();
    }
    stack_delete(stack);
    return 0;
}