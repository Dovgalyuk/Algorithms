#include <iostream> 
#include "../LibraryCPP/stack.h"
#include <cctype>
#include <fstream>

using namespace std;

int main() {
    Stack* stack = stack_create();
    ifstream input;
    input.open("input.txt");
    if (!input.is_open()) {
        cout << "Open error\n";
        system("pause");
        exit(0);
    }

    bool answ = true, star = true;
    int i = 0;
    char tag;
    
    while ((input.get(tag)) && (answ)) {
        tag = tolower(tag);
        if ((tag != '*') && (star)) {
            stack_push(stack, tag);
        }
        else { 
            if (star) {
                i++;
                input.get(tag);
            }
            star = false;
        }
        if (stack_empty(stack)) answ = false;
        if ((!star) && (answ)) {
            if (stack_get(stack) == tag) {
                stack_pop(stack);
            }
            else {
                answ = false;
            }
        } 
        i++;
    } 
    input.close();
    if (answ) cout << "Yes";
    else cout << "No";
    stack_delete(stack);
    return 0;
}