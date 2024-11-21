#ifndef ALG_LAB3_H
#define ALG_LAB3_H

#include <vector>
#include <string>

struct Point {
    int row;
    int col;

    bool operator==(const Point& other) const {
        return row == other.row && col == other.col;
    }
};

using Maze = std::vector<std::string>;

bool is_valid(int row, int col, const Maze& maze, const std::vector<std::vector<bool>>& visited);
void bfs(Maze& maze, Point start, Point end, bool& solvable);

#endif