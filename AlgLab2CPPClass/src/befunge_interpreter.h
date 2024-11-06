#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <functional>
#include <string>
#include <ostream>
#include "stack.h"

class Interpreter {
public:
    Interpreter();
    void run(const std::string &program, std::ostream& output);

private:
    Stack stack_;
    void execute(char command, std::ostream& output);
    int pop();
    int getTop() const;
    void performBinaryOp(const std::function<int(int, int)>& operation);
};

#endif