#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "stack.h"
#include <functional>
#include <string>

class Interpreter {
public:
    Interpreter();
    void run(const std::string &program);

private:
    Stack stack_;

    void execute(char command);

    int pop();
    int getTop() const;

    void performBinaryOp(const std::function<int(int, int)>& operation);
};

#endif
