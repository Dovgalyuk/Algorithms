#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"
#include "list.h"

using namespace std;

int opToNums(char op) {
    switch (op) {
        case '+': return -1;
            break;
        case '-': return -2;
            break;
        case '*': return -3;
            break;
        case '/': return -4;
            break;
        default: return -5;
    }
}

string read_line(ifstream& input)
{
    string line;
    getline(input, line);
    return line;
}

int prec(int op) {
    if(op==-3 || op==-4) return 2;
    if(op==-1 || op == -2) return 1;
    return 0;
}

void appOp(Stack* vals, int op) {
    int right = stack_get(vals);
    stack_pop(vals);
    int left= stack_get(vals);
    stack_pop(vals);
    switch(op) {
        case -1:
            stack_push(vals,left+right); break;
        case -2:
            stack_push(vals,left-right); break;
        case -3:
            stack_push(vals,left*right); break;
        case -4:
            stack_push(vals,left/right); break;
    }
}

List* infixToPostfix(const string& ex, int* count) {
    Stack* ops = stack_create();
    List* postfix = list_create();
    string number;

    for (size_t i = 0; i < ex.length(); i++) {
        char c = ex[i];
        if (isdigit(c)) {
            number += c;
        } else {
            if (!number.empty()) {
                int num = atoi(number.c_str());
                list_insert(postfix, num);
                number.clear();
            }
            if (c == '(') {
                stack_push(ops, opToNums(c));
            } else if (c == ')') {
                while (!stack_empty(ops) && stack_get(ops) != -5) {
                    list_insert(postfix, stack_get(ops));
                    stack_pop(ops);
                }
                stack_pop(ops);
            } else {
                while (!stack_empty(ops) && prec(stack_get(ops)) >= prec(opToNums(c))) {
                    list_insert(postfix, stack_get(ops));
                    stack_pop(ops);
                }
                stack_push(ops, opToNums(c));
            }
        }
    }
    if (!number.empty()) {
        int num = atoi(number.c_str());
        list_insert(postfix, num);
    }
    while (!stack_empty(ops)) {
        list_insert(postfix, stack_get(ops));
        stack_pop(ops);
    }
    stack_delete(ops);
    return postfix;
}

int resPost(List* postfix) {
    Stack *val = stack_create();
    while(!list_empty(postfix)) {
        if(list_item_data(list_last(postfix)) >= 0) {
            stack_push(val,list_item_data(list_last(postfix)));
        }else {
            appOp(val,list_item_data(list_last(postfix)));
        }
        if (list_second_to_last(postfix) == nullptr) {
            list_erase_first(postfix);
        }
        list_erase_next(postfix, list_second_to_last(postfix));
    }
    int result = stack_get(val);
    stack_delete(val);
    list_delete(postfix);
    return result;
}

int task1(string ex)
{
    int c = 0;
    List* postfix = infixToPostfix(ex, &c);
    return resPost(postfix);
}

bool testTask(int res1){
    if(res1 == 12) {
        return true;
    }
    return false;
}

int main(int argc, char **argv)
{
    ifstream input,output;
    input.open(argv[1]);

    if(!input.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }
    string ex = read_line(input);
    int res=task1(ex);

    if(!testTask(res)) {
        return 1;
    }
    cout<<res;
    output.close();
    input.close();
    return 0;
}
