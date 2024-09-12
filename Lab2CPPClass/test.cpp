#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char **argv) {
    std::ifstream file1(argv[1]);
    std::ifstream file2(argv[2]);

    if (!file1.is_open() || !file2.is_open()) {
        std::cerr << "Files is not open.\n";
        return 1;
    }

    std::string line1, line2;

    while (std::getline(file1, line1) && std::getline(file2, line2)) {
        if (line1 != line2) {
            return 1;
        }
    }

    if (std::getline(file1, line1) || std::getline(file2, line2)) {

        return 1;
    }

    return 0;
}
