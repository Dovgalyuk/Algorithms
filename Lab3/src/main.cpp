#include "maze.h"

#include <iostream>
#include <vector>
#include <cstdio>

int main(int argc, char** argv) {
    if (argc < 2)
        return 1;

    FILE* input = fopen(argv[1], "r");

    if (!input)
        return 1;

    Maze maze;

    if (!readMaze(input, maze)) {
        fclose(input);
        return 1;
    }

    fclose(input);

    int start = findStart(maze);

    if (start == -1)
        return 1;

    int width = maze[0].size();
    int height = maze.size();

    int finish = -1;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (maze[i][j] == 'Y')
                finish = i * width + j;
        }
    }

    if (finish == -1)
        return 1;

    std::vector<int> parent(height * width, -1);

    if (!findPath(maze, start, parent)) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }

    restorePath(maze, start, finish, parent);
    printMaze(maze);

    return 0;
}