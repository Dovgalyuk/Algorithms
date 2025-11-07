#include "stack.h"
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
using namespace std;
class Processor {
private:
  Stack *stack;
  map<string, int> registers;

public:
  Processor() {
    stack = stack_create();
    registers["A"] = 0;
    registers["B"] = 0;
    registers["C"] = 0;
    registers["D"] = 0;
  }

  ~Processor() { stack_delete(stack); }

  void execute(const string &operation) {
    istringstream iss(operation);
    string command;
    iss >> command;

    if (command == "PUSH") {
      string param;
      iss >> param;

      if (isdigit(param[0]) || param[0] == '-') {
        int value = stoi(param);
        stack_push(stack, value);
      } else {
        int value = registers[param];
        stack_push(stack, value);
      }
    } else if (command == "POP") {
      string reg;
      iss >> reg;

      if (!stack_empty(stack)) {
        int value = stack_get(stack);
        registers[reg] = value;
        stack_pop(stack);
      }

    } else if (command == "ADD") {
      string reg;
      iss >> reg;

      if (!stack_empty(stack)) {
        int second = stack_get(stack);
        stack_pop(stack);

        if (!stack_empty(stack)) {
          int first = stack_get(stack);
          stack_pop(stack);

          int result = first + second;
          registers[reg] = result;
        } else {
          stack_push(stack, second);
        }
      }
    } else if (command == "SUB") {
      string reg;
      iss >> reg;

      if (!stack_empty(stack)) {
        int second = stack_get(stack);
        stack_pop(stack);

        if (!stack_empty(stack)) {
          int first = stack_get(stack);
          stack_pop(stack);

          int result = first - second;
          registers[reg] = result;
        } else {
          stack_push(stack, second);
        }
      }
    } else if (command == "MUL") {
      string reg;
      iss >> reg;

      if (!stack_empty(stack)) {
        int second = stack_get(stack);
        stack_pop(stack);

        if (!stack_empty(stack)) {
          int first = stack_get(stack);
          stack_pop(stack);

          int result = first * second;
          registers[reg] = result;
        } else {
          stack_push(stack, second);
        }
      }
    }
  }

  void printRegisters() {
    cout << "A = " << registers["A"] << endl;
    cout << "B = " << registers["B"] << endl;
    cout << "C = " << registers["C"] << endl;
    cout << "D = " << registers["D"] << endl;
  }
};

int main(int argc, char *argv[]) {
  ifstream inputFile(argv[1]);
  Processor processor;
  string line;
  while (getline(inputFile, line)) {
    if (!line.empty()) {
      processor.execute(line);
    }
  }
  processor.printRegisters();
  inputFile.close();
  return 0;
}
