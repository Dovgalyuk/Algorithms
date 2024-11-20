#include "alg_lab3.h"
#include <iostream>
#include <fstream>

void process_maze(std::istream& input, std::ostream& output) {
    std::vector<std::string> maze;
    std::string line;
    Point start{-1, -1}, end{-1, -1};

    int row = 0;
    while (std::getline(input, line)) {
        if (line == "") {
            break;
        }

        for (int col = 0; col < static_cast<int>(line.size()); ++col) {
            if (line[col] == 'X') {
                start = {row, col};
            } else if (line[col] == 'Y') {
                end = {row, col};
            }
        }

        maze.push_back(line);
        ++row;
    }

    if (start.x == -1 || end.x == -1) {
        output << "Error: Start or end point missing in the input.\n";
        return;
    }

    bool solvable = false;
    bfs(maze, start, end, solvable);

    if (!solvable) {
        output << "IMPOSSIBLE\n\n";
    } else {
        for (const auto& row : maze) {
            output << row << '\n';
        }
        output << '\n';
    }
}

int main(int argc, char* argv[]) {
    std::ifstream inputFile;
    std::ofstream outputFile;

    if (argc == 3) {
        inputFile.open(argv[1]);
        outputFile.open(argv[2]);

        if (!inputFile || !outputFile) {
            std::cerr << "Error opening file!\n";
            return 1;
        }

        while (true) {
            process_maze(inputFile, outputFile);
            std::string next;
            std::getline(inputFile, next);
            if (next == "0") {
                break;
            }
        }

        inputFile.close();
        outputFile.close();
    } else {
        while (true) {
            process_maze(std::cin, std::cout);
            std::string next;
            std::getline(std::cin, next);
            if (next == "0") {
                break;
            }
        }
    }

    return 0;
}