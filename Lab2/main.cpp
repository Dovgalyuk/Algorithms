#include <iostream>
#include <string>
#include "BeatnikInterpreter.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <script_file> <input_file>" << std::endl;
        return 1;
    }
    BeatnikInterpreter interpreter(argv[2]);
    interpreter.run(argv[1]);
    return 0;
}