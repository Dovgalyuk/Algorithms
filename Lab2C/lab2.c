#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

int main(int argc, char **argv)
{
    if (argc != 3){
        printf("always need 2 txt files. Input can be empty but need to exist");
        return -1;
    }
    Maze *maze = maze_load(argv[1]);
    if (!maze) {
        printf("maze didnt load - %s\n", argv[1]);
        return -1;
    }
    if (!maze->stack) {
        printf("stack not created\n");
        maze_free(maze);
        return -2;
    }
    FILE *input = fopen(argv[2], "r");
    if (!input) {
        maze_free(maze);
        return -3;
    }
    int res = -4;
    while (1) {
        char cmd = maze_get(maze, maze->x, maze->y);
        int status = execute_command(maze, cmd, input);
        if (status == -1) {
            printf("read command (%c) error at %d, %d\n", cmd, maze->x, maze->y);
            break;
        }
        if (status == 1) {
            res = EXIT_SUCCESS;
            break;
        }
        check_rat_alive(maze);
        if (!move_rat(maze)) {
            printf("Rat stuck at %d, %d\n", maze->x, maze->y);
            break;
        }
    }
    fclose(input);
    maze_free(maze);
    return res;
}
