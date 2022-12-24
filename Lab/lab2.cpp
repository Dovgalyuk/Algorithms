#include <iostream>
#include <string>
#include "stack.h"
using namespace std;

int main() {
    Stack* stack = stack_create();

    size_t size;
    int k = 0;
    cin >> size;
    cin.ignore();
    string buf;
    getline(cin, buf);

    while ((buf.find("push ") == 0) || (buf.find("pop") == 0)) {
        if ((buf.find("push") == 0) && (buf.find_first_of("0123456789", 5) == 5)) {
            if (k != size) {
                string str = buf.substr(5);
                int o = stoi(str);
                stack_push(stack, o);
                k += 1;
            }
            else {
                cout << "BAD PUSH\n";
            }
        }
        if ((buf.find("pop") == 0)) {
            if (!stack_empty(stack)) {
                cout << stack_get(stack) << "\n";
                stack_pop(stack);
                k -= 1;
            }
            else {
                cout << "BAD POP\n";
            }
        }
        getline(cin, buf);
    }

    
    for (int i = 0; i < size;i++) {
        cout << stack_get(stack) << "\n";
        stack_pop(stack);
    }
    stack_delete(stack);
    return 0;
}
