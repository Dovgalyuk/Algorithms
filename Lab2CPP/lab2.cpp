#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "stack.h"

using namespace std;

string read_line(ifstream& input)
{
    string line;
    getline(input, line);
    return line;
}

int prec(char op) {
    if(op=='*' || op=='/') return 2;
    if(op=='+' || op == '-') return 1;
    return 0;
}

void appOp(Stack* vals, char op) {
    int right= stack_get(vals);
    stack_pop(vals);
    int left= stack_get(vals);
    stack_pop(vals);
    switch(op) {
        case '+':
            stack_push(vals,left+right); break;
        case '-':
            stack_push(vals,left-right); break;
        case '*':
            stack_push(vals,left*right); break;
        case '/':
            stack_push(vals,left/right); break;
    }
}

vector<string> infixToPostfix(const string& ex) {
    Stack* ops = stack_create();
    vector<string> postfix;
    string number;

    for (size_t i = 0; i < ex.length(); i++) {
        char c = ex[i];
        if (isdigit(c)) {
            number += c;
        } else {
            if (!number.empty()) {
                postfix.push_back(number);
                number.clear();
            }
            if (c == '(') {
                stack_push(ops, c);
            } else if (c == ')') {
                while (!stack_empty(ops) && stack_get(ops) != '(') {
                    postfix.push_back(string(1, stack_get(ops)));
                    stack_pop(ops);
                }
                stack_pop(ops);
            } else {
                while (!stack_empty(ops) && prec(stack_get(ops)) >= prec(c)) {
                    postfix.push_back(string(1, stack_get(ops)));
                    stack_pop(ops);
                }
                stack_push(ops, c);
            }
        }
    }
    if (!number.empty()) {
        postfix.push_back(number);
    }
    while (!stack_empty(ops)) {
        postfix.push_back(string(1, stack_get(ops)));
        stack_pop(ops);
    }
    stack_delete(ops);
    return postfix;
}

int resPost(const vector<string>& postfix) {
    Stack *val = stack_create();
    for(const string& token:postfix) {
        if(isdigit(token[0])) {
            stack_push(val,stoi(token));
        }else {
            appOp(val,token[0]);
        }
    }
    int result = stack_get(val);
    stack_delete(val);
    return result;
}

int task1(string ex)
{
    vector<string> postfix = infixToPostfix(ex);
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
