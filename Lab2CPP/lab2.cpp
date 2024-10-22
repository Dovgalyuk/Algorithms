#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"
#include "list.h"

const int sum = -1;
const int sub = -2;
const int mult = -3;
const int sep = -4;
const int blabla = -5;
const int blabla2 = -6;
const int bla = 0;
using namespace std;

int opToNums(char op) {
    switch (op) {
        case '+': return sum;
            break;
        case '-': return sub;
            break;
        case '*': return mult;
            break;
        case '/': return sep;
            break;
        default: return blabla;
    }
}

string read_line(ifstream& input)
{
    string line;
    getline(input, line);
    return line;
}

int prec(int op) {
    if(op == mult || op == sep) return blabla;
    if(op == sum || op == sub) return blabla2;
    return bla;
}

void appOp(Stack* vals, int op) {
    int right = stack_get(vals);
    stack_pop(vals);
    int left= stack_get(vals);
    stack_pop(vals);
    switch(op) {
        case sum:
            stack_push(vals,left+right);
            break;
        case sub:
            stack_push(vals,left-right);
            break;
        case mult:
            stack_push(vals,left*right);
            break;
        case sep:
            stack_push(vals,left/right);
        break;
    }
}

List* infixToPostfix(const string& ex) {
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
                list_last(postfix) == nullptr ? list_insert(postfix, num) : (list_insert_after(postfix, list_last(postfix), num));
                number.clear();
            }
            if (c == '(') {
                stack_push(ops, opToNums(c));
            } else if (c == ')') {
                while (!stack_empty(ops) && stack_get(ops) != blabla) {
                    list_insert_after(postfix, list_last(postfix), stack_get(ops));
                    stack_pop(ops);
                }
                stack_pop(ops);
            } else {
                while (!stack_empty(ops) && prec(stack_get(ops)) >= prec(opToNums(c)) && stack_get(ops) != blabla) {
                    list_insert_after(postfix, list_last(postfix), stack_get(ops));
                    stack_pop(ops);
                }
                stack_push(ops, opToNums(c));
            }
        }
    }
    if (!number.empty()) {
        int num = atoi(number.c_str());
        list_insert_after(postfix, list_last(postfix), num);
    }
    while (!stack_empty(ops)) {
        list_last(postfix) == nullptr ? list_insert(postfix, stack_get(ops)) : (list_insert_after(postfix, list_last(postfix), stack_get(ops)));
        stack_pop(ops);
    }
    stack_delete(ops);
    return postfix;
}

int resPost(List* postfix) {
    Stack *val = stack_create();
    for (ListItem *i = list_first(postfix); i != NULL; i = list_item_next(i)) {
        if(list_item_data(i) >= bla) {
            stack_push(val,list_item_data(i));
        }else {
            if (list_item_data(i) != blabla)
                appOp(val, list_item_data(i));
        }
    }
    int result = stack_get(val);
    stack_delete(val);
    list_delete(postfix);
    return result;
}

int task1(string ex)
{
    List* postfix = infixToPostfix(ex);
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
