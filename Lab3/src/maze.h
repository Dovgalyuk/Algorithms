#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <string>
#include <cstdio>

using Maze = std::vector<std::string>;

bool readMaze(FILE* input, Maze& maze);
int findStart(const Maze& maze);
bool findPath(const Maze& maze, int start, std::vector<int>& parent);
void restorePath(Maze& maze, int start, int finish, const std::vector<int>& parent);
void printMaze(const Maze& maze);

#endif