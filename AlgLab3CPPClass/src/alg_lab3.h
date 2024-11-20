#ifndef ALG_LAB3_H
#define ALG_LAB3_H

#include <vector>
#include <string>

struct Point {
    int x, y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

void bfs(std::vector<std::string>& maze, Point start, Point end, bool& solvable);

#endif