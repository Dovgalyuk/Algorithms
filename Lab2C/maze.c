#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "maze.h"

#define MAX_LINES 1000
#define MAX_LINE_LEN 1000
#define MAX_STEPS_WITHOUT_FOOD 10
#define OVERFEED_INTERVAL 4

Maze* maze_load(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return NULL;
    
    Maze *maze = malloc(sizeof(Maze));
    if (!maze) { fclose(f); return NULL; }
    
    char **lines = malloc(MAX_LINES * sizeof(char*));
    if (!lines) { 
        fclose(f);
        free(maze);
        return NULL; 
    }
    int h = 0;
    int w = 0;
    char buf[MAX_LINE_LEN];
    
    while (fgets(buf, sizeof(buf), f) && h < MAX_LINES) {
        int len = strlen(buf);
        while (len > 0 && (buf[len-1] == '\n' || buf[len-1] == '\r')) {
            buf[--len] = '\0';
        }
        lines[h] = strdup(buf);
        if (!lines[h]) break;
        if (len > w) w = len;
        h++;
    }
    fclose(f);
    
    maze->grid = malloc(h * sizeof(char*));
    if (!maze->grid) {
        for (int i = 0; i < h; i++) free(lines[i]);
        free(lines);
        free(maze);
        return NULL;
    }
    
    for (int i = 0; i < h; i++) {
        maze->grid[i] = calloc(w + 1, sizeof(char));
        if (!maze->grid[i]) {
            for (int j = 0; j < i; j++) free(maze->grid[j]);
            free(maze->grid);
            for (int j = 0; j < h; j++) free(lines[j]);
            free(lines);
            free(maze);
            return NULL;
        }
        memset(maze->grid[i], ' ', w);
        memcpy(maze->grid[i], lines[i], strlen(lines[i]));
        free(lines[i]);
        lines[i] = NULL;
    }
    free(lines);
    
    maze->h = h;
    maze->w = w;
    maze->dir = 0;
    maze->x = -1;
    maze->y = -1;
    maze->steps_after_food = 0;
    maze->food_count = 0;
    maze->step = 0;
    maze->last_food_step = 0;
    maze->A = 0;
    maze->B = 0;
    maze->stack = stack_create(NULL);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (maze->grid[y][x] == 'S') {
                maze->x = x;
                maze->y = y;
                return maze;
            }
        }
    }
    
    printf("Start 'S' not found\n");
    maze_free(maze);
    return NULL;
}

void maze_free(Maze *maze) {
    if (!maze) return;
    if (maze->grid) {
        for (int i = 0; i < maze->h; i++) {
            free(maze->grid[i]);
        }
        free(maze->grid);
    }
    stack_delete(maze->stack);
    free(maze);
}

char maze_get(const Maze *maze, int x, int y){
    if (!maze || !maze->grid) return ' ';
    if (x < 0 || x >= maze->w) return ' ';
    if (y < 0 || y >= maze->h) return ' ';
    return maze->grid[y][x];
}

bool maze_is_wall(const Maze *maze, int x, int y){
    if (!maze || !maze->grid) return true;
    if (x < 0 || x >= maze->w) return true;
    if (y < 0 || y >= maze->h) return true;
    char c = maze->grid[y][x];
    return c == ' ' || c == '\0';
}

int execute_command(Maze *maze, char cmd, FILE *input) {
    if (!maze || !maze->stack) {
        return -1;
    }
    switch (cmd) {
        case 'a':
            maze->A = (maze->A + 1) % 256;
            break;

        case 'b':
            maze->B = (maze->B + 1) % 256;
            break;
        
        case 'A':
            maze->A = (maze->A + 255) % 256;
            break;

        case 'B':
            maze->B = (maze->B + 255) % 256;
            break;

        case 'z':
            maze->A = 0;
            break;

        case 'Z':
            maze->B = 0;
            break;

        case 'P':
            stack_push(maze->stack, maze->A);
            break;

        case 'p':
        case 'r':
        case 'o':
        case 'O':
        case 'd': {
            if (stack_empty(maze->stack)) break;
            uintptr_t value = stack_get(maze->stack);
            stack_pop(maze->stack);
            switch (cmd) {
                case 'p':
                    if (printf("%zu\n", value) < 0) return -1;
                    break;

                case 'r':
                    if (putchar(value) == EOF) return -1;
                    printf("\n"); // from original realization
                    break;

                case 'o':
                    maze->A = value;
                    break;

                case 'O':
                    maze->B = value;
                    break;

                case 'd':
                    break;
            }
            break;
        }
        case 'R':
            while (!stack_empty(maze->stack)) {
                int ch = (unsigned char)stack_get(maze->stack);
                stack_pop(maze->stack);
                if (putchar(ch) == EOF) return -1;
            }
            printf("\n"); // from original realization
            break;
        
        case 'i': {
            if (!input) {
                fprintf(stderr, "Input file is not open\n");
                return -1;
            }
            Stack *temp = stack_create(NULL); 
            if (!temp) return -1;
            int ch;
            while ((ch = fgetc(input)) != EOF && ch != '\n') {
                stack_push(temp, ch);
            }
            if (!stack_empty(temp) && stack_get(temp) == '\r') stack_pop(temp);
            if (ferror(input)) {
                stack_delete(temp);
                return -1;
            }
            while (!stack_empty(temp)) {
                stack_push(maze->stack, stack_get(temp));
                stack_pop(temp);
            }
            stack_delete(temp);    
            break;
        }

        case 'c':
            eat_cheese(maze);
            break;

        case 'C':
            return 1;

        case '+':
        case 'S':
            break;

        case 'T':
        case 'Y':
        case '^':
        case '>':
        case '<':
        case 'v':
            break; // all this used in move_rat

        default:
            printf( "wrong char '%c'\n", cmd);
            return -1;
    }
    return 0;
}


void check_rat_alive(Maze *maze) {
    if (maze->steps_after_food >= MAX_STEPS_WITHOUT_FOOD) {
        printf("Rat died of hunger at step %d\n", maze->step);
        maze_free(maze);
        exit(1);
    }
}

void eat_cheese(Maze *maze) {
    if (maze->step - maze->last_food_step < OVERFEED_INTERVAL) {
        maze->food_count++;
        if (maze->food_count >= 3) {
            printf("Rat overfed at step %d\n", maze->step);
            maze_free(maze);
            exit(1);
        }
    } else {
        maze->food_count = 1;
    }
    
    maze->last_food_step = maze->step;
    maze->steps_after_food = 0;
}

bool move_rat(Maze *maze)
{
    if (!maze || !maze->grid) return false;
    const int dx[4] = { 0, 1, 0, -1 };
    const int dy[4] = { -1, 0, 1, 0 };
    const int turns[4] = { 3, 0, 1, 2 };
    const char block[4] = { 'v', '<', '^', '>' };
    char cur = maze_get(maze, maze->x, maze->y);
    bool left_block = (cur == 'T' && maze->B != 0) || (cur == 'Y' && maze->A != maze->B);
    for (int i = 0; i < 4; i++) {
        if (i == 0 && left_block) continue;
        int dir = (maze->dir + turns[i]) % 4;
        int x = maze->x + dx[dir];
        int y = maze->y + dy[dir];
        if (maze_is_wall(maze, x, y)) continue;
        
        if (maze_get(maze, x, y) == block[dir]) continue;
        maze->x = x;
        maze->y = y;
        maze->dir = dir;
        maze->step++;
        maze->steps_after_food++;
        return true;
    }
    return false;
}
