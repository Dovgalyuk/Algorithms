#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

using namespace std;

bool isPair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}') ||
           (open == '<' && close == '>');
}

bool isOpening(char c) {
    return c == '('  c == '['  c == '{' || c == '<';
}

int main(int argc, char **argv) {

    return 0;
}