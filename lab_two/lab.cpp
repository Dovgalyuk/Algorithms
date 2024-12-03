#include <iostream>
#include <fstream>
#include <vector>
#include "stack.h"

using namespace std;

bool test (Stack *stack, vector<char> &w, size_t &count);

int main(int argc, char* argv[]) {

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <file_path>" << endl;
        return 1;
    }

    ifstream input(argv[1]);

    if (!input) {
        cout << "Opening error" <<  endl;
        return 1;
    }

    char c;
    size_t count = 0;
    vector<char> w;

    Stack* stack = stack_create();

    while (input.get(c)) {
        if (c == '*') { 
            break;
        }
        stack_push(stack, c);
        count++;
    }

    while (input.get(c)) w.push_back(c);

    if (test(stack, w, count)) cout << "YES";
    else cout << "NO";

    stack_delete(stack);

    input.close();
}

bool test (Stack *stack, vector<char> &w, size_t &count) {
    if (count != w.size()) {
        return false;
    }

    for (char c : w) {
        if (stack_empty(stack) || stack_get(stack) != c) return false;
        stack_pop(stack);
    }

    return true;
}