#include "lab2.h"
#include <iostream>

using namespace std;
int main(int argc, char** argv) {

    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    ifstream input(argv[1]);
    if (!input.is_open()) {
        cout << "file open error\n";
        return 1;
    }

    Stack* stack = stack_create(); 


    if (validate_tag_sequence(input, stack)) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }

    stack_delete(stack);
    input.close();
    return 0;
}
