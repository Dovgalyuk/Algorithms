#include <iostream>
#include <fstream>
#include "stack.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc < 2)
        return 1;

    ifstream input(argv[1]);
    if (!input.is_open())
        return 1;

    int max_size;
    input >> max_size;

    Stack stack;
    int len = 0;

    string comm;
    while (input >> comm) {
        if (comm == "push") {
            Data value;
            input >> value;
            if (len < max_size) {
                stack.push(value);
                len++;
            } else
                cout << "BAD PUSH" << "\n";
        } 
        else if (comm == "pop") {
            if (stack.empty())
                cout << "BAD POP" << "\n";
            else {
                cout << stack.get() << "\n";
                stack.pop();
                len--;
            }
        }
    }

    cout << "STACK" << "\n";
    
    if (!stack.empty()) {
    
        Stack tmp;
        while (!stack.empty()) {
            tmp.push(stack.get());
            stack.pop();
            
        }
        
        while (!tmp.empty()) {
            cout << tmp.get() << "\n";
            tmp.pop();
        }
    }

    input.close();
    return 0;
}