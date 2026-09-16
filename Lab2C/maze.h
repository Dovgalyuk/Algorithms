#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdbool.h>
#include "stack.h"

typedef struct Maze Maze;

Maze* maze_load(const char *filename);
void maze_free(Maze *maze);
char maze_get(const Maze *maze, int x, int y);
bool maze_is_wall(const Maze *maze, int x, int y);
int execute_command(Maze *maze, char cmd, FILE *input);
void check_rat_alive(Maze *maze);
void eat_cheese(Maze *maze);
bool move_rat(Maze *maze);
#endif
