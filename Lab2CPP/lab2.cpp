#include <iostream>
#include <fstream>
#include "stack.h"
using namespace std;

int main(__attribute__((unused)) int argc, char** argv){
    ifstream input(argv[1]);
    Stack *stack = stack_create();
    string line;
    int flag = 0;
    while(input.eof() == 0){
        input >> line;
        if(line[1] == '/'){
            int i = 0;
            while(1){
                char c = stack_get(stack);
                stack_pop(stack);
                if(c == 60){
                    break;
                } else if (line[line.size()-1-i] == '/'){
                    i++;
                } else if(c != line[line.size()-1-i]){
                    flag++;
                    break;
                } else {
                    i++;
                }
            }
            i = 0;
        } else {
            for(char c: line){
                stack_push(stack, c);
            }
        }
    }
    if(flag){
        cout << "NO";
    } else {
        cout << "YES";                      
    }
    
stack_delete(stack);
return 0;           
}
