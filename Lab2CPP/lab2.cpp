#include <iostream>
#include <fstream>
#include "stack.h"
using namespace std;
 
int main(__attribute__((unused)) int argc, char** argv){
    ifstream input(argv[1]);
    Stack *stack = stack_create();
    string line;
    int flag = 0;
    int od_kav = 0;
    int dv_kav = 0;
    char c;
    while(input.get(c)) {
        if(c == '('){
            stack_push(stack, c);
        } else if(c == ')'){
            if(stack_get(stack) != '('){
                flag++;
                break;
            } else {
                stack_pop(stack);
            }
        } else if(c == '\''){
            if(od_kav && stack_get(stack) == c){
                stack_pop(stack);
            } else if(!od_kav){
                stack_push(stack, c);
                od_kav++;
            } else {
                flag++;
                break;
            }
        } else if(c == '\"'){
            if(dv_kav && stack_get(stack) == c){
                stack_pop(stack);
            } else if(!dv_kav){
                stack_push(stack, c);
                dv_kav++;
            } else {
                flag++;
                break;
            }
        }
    }
    if(flag){
        cout << "NO";
    } else {
        cout << "YES";
    }

    return 0;           
}
