#include <iostream>
#include <fstream>
#include <string>
#include "vector.h"
#include "queue.h"

typedef Vector<std::string> vstr;

struct Position {
    int row, col;
};

int bfs(vstr& maze, Position start) {
    const int dRow[] = {-1, 1, 0, 0};
    const int dCol[] = {0, 0, -1, 1};

    Queue<Position> queue;
    queue.insert(start);

    vstr visited;
    visited.resize(maze.size());
    for(size_t i = 0; i < maze.size(); i++) {
        visited.set(i, std::string(maze.get(0).size(), '0'));
    }

    visited.get(start.row)[start.col] = '1';

    while (!queue.empty()) {
        Position current = queue.get();
        queue.remove();

        if (isdigit(maze.get(current.row)[current.col])) {
            return maze.get(current.row)[current.col] - '0';
        }

        for (int i = 0; i < 4; ++i) {
            size_t newRow = static_cast<size_t>(current.row + dRow[i]);
            size_t newCol = static_cast<size_t>(current.col + dCol[i]);

            if (newRow < maze.size() &&
                newCol < maze.get(0).size() &&
                maze.get(newRow)[newCol] != '#' && visited.get(newRow)[newCol] == '0') {
                visited.get(newRow)[newCol] = '1';
                queue.insert({static_cast<int>(newRow), static_cast<int>(newCol)});
            }
        }
    }

    return -1; // If not found
}

int main(int argc, char** argv) {

    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        throw std::runtime_error("Failed to open input file.");
    }

    vstr maze;
    std::string line;
    while (std::getline(input, line)) {
        maze.resize(maze.size() + 1);
        maze.set(maze.size() - 1, line);
    }
    input.close();

    Position start{-1, -1};
    for (size_t i = 0; i < maze.size(); ++i) {
        for (size_t j = 0; j < maze.get(i).size(); ++j) {
            if (maze.get(i)[j] == 'X') {
                start = {static_cast<int>(i), static_cast<int>(j)};
                maze.get(i)[j] = '.';
                break;
            }
        }
        if (start.row != -1) break;
    }

    if (start.row == -1) {
        throw std::runtime_error("Start position 'X' not found in the maze.");
    }

    int nearestDigit = bfs(maze, start);

    std::ofstream output(argv[2]);
    if (!output.is_open()) {
        throw std::runtime_error("Failed to open output file.");
    }

    output << nearestDigit << std::endl;

    output.close();

    return 0;
}
