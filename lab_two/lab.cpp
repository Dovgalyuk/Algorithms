#include <iostream>
#include <fstream>
#include "../LibraryCPP/stack.h"

using namespace std;

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
    bool test = 1;
    Stack* stack = stack_create();

    while (input.get(c)) {
        if (c == '*') { 
            break;
        }
        stack_push(stack, c);
    }

    while (input.get(c)) {
        if (stack_empty(stack) || stack_get(stack) != c) {
            test = 0;
            break;
        }
        stack_pop(stack);
    }

    if (test && stack_empty(stack)) cout << "YES";
    else cout << "NO";

    stack_delete(stack);

    input.close();
}
