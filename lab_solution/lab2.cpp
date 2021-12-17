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
    char tag;

    while ((input.get(tag)) && (answ)) {  //while file is being read and the lines are matches
        tag = tolower(tag);
        if ((tag != '*') && (star)) { //is executed before multipl(*) occurs
            stack_push(stack, tag);
        }
        else {
            if (star) { //when multipl(*) is encoured
                 star = false;
                 continue;
            }    
        }

        if (stack_empty(stack)) answ = false; //if 2 line is longer than 1

        if ((!star) && (answ)) {   //if multiplication(*) has already occured and the lines match
            if (stack_get(stack) == tag) {
                stack_pop(stack);
            }
            else {
                answ = false;
            }
        }
    }
    input.close();
    if ((answ) && (stack_empty(stack))) cout << "Yes";
    else cout << "No";
    stack_delete(stack);
    return 0;
}
