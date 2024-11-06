#include <iostream>
#include <fstream>
#include "stack.h"

using namespace std;

int main(__attribute__((unused)) int argc, char** argv){
    ifstream input(argv[1]);
    Stack *stack = stack_create();
    string line;
    int flag = 0;
    while(getline(input, line)) {
        if(line[1] == '/'){
            string a = stack_get(stack);
            int i = 2;
            while(line[i]!='\0'){
                if(a[i-1] != line[i]){
                    flag++;
                    break;
                }
                i++;
            }
            if(flag){
                cout << "NO";
                break;
            } else {
                flag = 0;
                stack_pop(stack);   
            }
        } else {
            stack_push(stack, line);
        }
    }
    if(!flag){
        cout << "YES";
    }
    stack_delete(stack);
    return 0;           
}