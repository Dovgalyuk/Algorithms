#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include "stack.h"

void separation(std::string &command, std::string &value)
{
    size_t space = command.find(' ');
    if (space == std::string::npos)
    {
        value = "";
        return;
    }
    value = command.substr(space + 1);
    command = command.substr(0, space);
}

void push(Stack<std::string> &stack, int *reg, const std::string& value)
{
    if(value.empty()){
        throw std::runtime_error("BAD PUSH");
    }

    else if (std::isdigit(value[0]) || (value.size() > 1 && value[0] == '-' && std::isdigit(value[1])))
    {
        stack.push(value);
    }

    else
    {
        size_t index = value[0] - 'A';
        if (index < 4)
        {
            stack.push(std::to_string(reg[index]));
        }
        else{
            throw std::runtime_error("BAD PUSH");
        }
    }
}

void pop(Stack<std::string> &stack, int *reg, const std::string &value)
{
    if (stack.empty() || value.empty()|| stack.get() == "ADDR")
    {
        throw std::runtime_error("BAD POP");
    }

    else if (std::isalpha(value[0]))
    {
        size_t index = value[0] - 'A';

        if (index < 4)
        {
            reg[index] = std::stoi(stack.get());
            stack.pop();
            return;
        }
    }

    throw std::runtime_error("BAD POP");
}

void add(Stack<std::string> &stack)
{

    if(stack.empty() || stack.get()=="ADDR"){
        throw std::runtime_error("BAD ADD");
    }

    int a1 = std::stoi(stack.get());
    stack.pop();

    if(stack.empty() || stack.get()=="ADDR"){
        throw std::runtime_error("BAD ADD");
    }

    int a2 = std::stoi(stack.get());
    stack.pop();

    stack.push(std::to_string(a1+a2));
}

void sub(Stack<std::string> &stack)
{
    if(stack.empty() || stack.get()=="ADDR"){
        throw std::runtime_error("BAD SUB");
    }

    int a1 = std::stoi(stack.get());
    stack.pop();

    if(stack.empty() || stack.get()=="ADDR"){
        throw std::runtime_error("BAD SUB");
    }

    int a2 = std::stoi(stack.get());
    stack.pop();

    stack.push(std::to_string(a2-a1));
}

void mul(Stack<std::string> &stack)
{
    if(stack.empty() || stack.get()=="ADDR"){
        throw std::runtime_error("BAD MUL");
    }

    int a1 = std::stoi(stack.get());
    stack.pop();

    if(stack.empty() || stack.get()=="ADDR"){
        throw std::runtime_error("BAD MUL");
    }

    int a2 = std::stoi(stack.get());
    stack.pop();

    stack.push(std::to_string(a1*a2));
}

void call(Stack<std::string> &stack)
{
    stack.push("ADDR");
}

void ret(Stack<std::string> &stack)
{
    if(stack.empty()){
        throw std::runtime_error("BAD RET");
    }

    else if(stack.get()=="ADDR"){
        stack.pop();
        return;
    }

    throw std::runtime_error("BAD RET");
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return 1;
    }

    int reg[4]{0, 0, 0, 0};

    Stack<std::string> proc_stack;

    std::ifstream input_file(argv[1]);

    if (input_file.is_open())
    {

        std::string command;
        std::string value;
        try{

        while (std::getline(input_file, command))
        {
            separation(command, value);
            if(command.empty()) {
                continue;
            }
            else if (command == "push")
            {
                push(proc_stack, reg, value);
            }
            else if (command == "pop")
            {
                pop(proc_stack, reg, value);
            }
            else if (command == "add")
            {
                add(proc_stack);
            }
            else if (command == "sub")
            {
                sub(proc_stack);
            }
            else if (command == "mul")
            {
                mul(proc_stack);
            }
            else if (command == "call")
            {
                call(proc_stack);
            }
            else if (command == "ret")
            {
                ret(proc_stack);
            }
            else{
                throw std::runtime_error("BAD COM");
            }
        }}
        catch(const std::runtime_error& e){

            std::cerr<<e.what();

            return 1;
        }
        catch(...){

            return 1;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        printf("%c = %d\n", 'A' + i, reg[i]);
    }

    input_file.close();
    return 0;
}