#include "../LibraryCPPClass/stack.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char **argv) {
  Stack stack;
  int a = 0, b = 0, c = 0, d = 0;

  ifstream input_file(argv[1]);
  if (!input_file.is_open()) {
    cerr << "Error: Could not open file " << argv[1] << endl;
    return 1;
  }

  string line;
  string last_command = " ";
  bool error = false;
  while (getline(input_file, line) && !error) {
    istringstream iss(line);
    string command, number = " ";

    iss >> command;
    iss >> number;

    if (command == "push") {
      stack.push(stoi(number));
      last_command = command;
    }

    if (command == "pop") {
      if (last_command == "call") {
        cout << "BAD POP\n";
        error = true;
      } else {
        if (number == "A") {
          a = stack.get();
          stack.pop();
          last_command = command;
        }
        if (number == "B") {
          b = stack.get();
          stack.pop();
          last_command = command;
        }
        if (number == "C") {
          c = stack.get();
          stack.pop();
          last_command = command;
        }
        if (number == "D") {
          d = stack.get();
          stack.pop();
          last_command = command;
        }
      }
    }

    if (command == "call") {
      last_command = command;
    }

    if (command == "ret") {
      if (last_command == "push") {
        cout << "BAD RET\n";
        error = true;
      } else {
        last_command = command;
      }
    }

    if (command == "add") {
      int value = stack.get();
      stack.pop();
      value += stack.get();
      stack.pop();
      stack.push(value);
      last_command = command;
    }

    if (command == "sub") {
      int value = stack.get();
      stack.pop();
      value -= stack.get();
      stack.pop();
      stack.push(value);
      last_command = command;
    }

    if (command == "mul") {
      int value = stack.get();
      stack.pop();
      value *= stack.get();
      stack.pop();
      stack.push(value);
      last_command = command;
    }
  }

  if (!error) {
    cout << "A = " << a << endl
         << "B = " << b << endl
         << "C = " << c << endl
         << "D = " << d << endl;
  }

  input_file.close();
  return 0;
}
