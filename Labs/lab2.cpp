#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "list.h"

void execute_operations(List* stack, int vars[4], const std::string& operations);

std::string ReadFile() {
    std::ifstream inputFile("input.txt"); //D:\VisualStudioRepo\Algorithms\out\build\x64-debug\Labs - мое расположения файла. Он должен быть там, где собирается .exe файл решения
    std::string otv;
    if (!inputFile.is_open()) {
        std::cerr << "Open Error" << std::endl;
        return "ERROR";
    }
    std::string line;
    while (std::getline(inputFile, line)) {
        otv += line;
        otv += "\n";
    }
    inputFile.close();
    return otv;
}

int main()
{
    List* stack = list_create();
    int vars[4] = { 0, 0, 0, 0 };

    std::string operations = ReadFile();
    if (operations == "ERROR")
        return 0;

    execute_operations(stack, vars, operations);

    std::cout << "stack:\n";
    for (ListItem* item = list_first(stack); item != nullptr; item = list_item_next(item))
    {
        std::cout << list_item_data(item) << "\n";
    }

    std::cout << "vars:\n";
    for (int i = 0; i < 4; ++i)
    {
        std::cout << vars[i] << "\n";
    }

    list_delete(stack);

    return 0;
}

void execute_operations(List* stack, int vars[4], const std::string& operations)
{
    std::istringstream iss(operations);
    std::string operation;

    while (std::getline(iss, operation, '\n'))
    {
        std::istringstream iss_op(operation);
        std::string op;

        iss_op >> op;

        if (op == "bipush")
        {
            int num;
            iss_op >> num;
            list_insert(stack, num);
        }
        else if (op == "pop")
        {
            list_erase_first(stack);
        }
        else if (op == "iadd")
        {
            ListItem* top1 = list_first(stack);
            ListItem* top2 = list_item_next(top1);
            int result = list_item_data(top1) + list_item_data(top2);
            list_erase_first(stack);
            list_erase_first(stack);
            list_insert(stack, result);
        }
        else if (op.find("istore_") != std::string::npos)
        {
            int var_index = op[op.length() - 1] - '0';
            vars[var_index] = list_item_data(list_first(stack));
            list_erase_first(stack);
        }
    }
}