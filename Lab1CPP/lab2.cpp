#include <iostream>
#include <fstream>
#include "list.h"
#include "stack.h"

struct Registers {
    int A = 0;
    int B = 0;
    int C = 0;
    int D = 0;
};

int main (int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " input_file" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input) {
        std::cerr << "Fail to open file" << std::endl;
        return -1;
    }

    Stack* stack = stack_create();

    return 0;
}