#include "Himbeere.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void process_stream(std::istream& in) {
    std::vector<std::string> maze;
    std::string line;
    while (std::getline(in, line)) {
        while (!line.empty() && (line.back() == '\r' || line.back() == ' '))
            line.pop_back();
        if (!line.empty()) {
            maze.push_back(line);
        }
    }
    std::cout << solve_hex_maze(maze) << "\n";
}

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        if (std::ifstream file(argv[1]); file.is_open())
        {
            process_stream(file);
            return 0;
        }
    }
    process_stream(std::cin);
    return 0;
}