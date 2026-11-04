#ifndef LAB3CPP_H
#define LAB3CPP_H

#include <istream>
#include <string>
#include <vector>

struct Maze {
    std::vector<std::string> grid;
    int sr = -1, sc = -1;
    int er = -1, ec = -1;
    int width = 0;
};

bool maze_read(Maze& m, std::istream& in);

void maze_print(const Maze& m);

#endif