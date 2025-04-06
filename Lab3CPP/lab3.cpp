#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "vector.h"

#define MAX_ROWS 100
#define MAX_COLS 100

typedef struct {
    int row;
    int col;
} Position;

int main() {
    char maze[MAX_ROWS][MAX_COLS];
    int rows = 0, cols = 0;
    Position start;
    int distances[MAX_ROWS][MAX_COLS];

    FILE *file;
    errno_t err = fopen_s(&file, "input.txt", "r");
    if (err != 0) {
        perror("Error opening input.txt");
        return 1;
    }

    while (fgets(maze[rows], MAX_COLS, file) != NULL) {
        char *newline = strchr(maze[rows], '\n');
        if (newline != NULL) {
            *newline = '\0';
        }
        for (int j = 0; maze[rows][j] != '\0'; j++) {
            if (maze[rows][j] == 'X') {
                start.row = rows;
                start.col = j;
            }
        }
        rows++;
    }

    fclose(file);
  
    cols = (int)strlen(maze[0]);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            distances[i][j] = -1;
        }
    }
    Queue *queue = queue_create();
    queue_insert(queue, (start.row * cols) + start.col); 
    distances[start.row][start.col] = 0;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!queue_empty(queue)) {
        int current_pos = queue_get(queue);
        queue_remove(queue);
        int current_row = current_pos / cols;
        int current_col = current_pos % cols;

        for (int i = 0; i < 4; i++) {
            int new_row = current_row + dr[i];
            int new_col = current_col + dc[i];

            if (new_row >= 0 && new_row < rows && new_col >= 0 && new_col < cols &&
                maze[new_row][new_col] != '#' && distances[new_row][new_col] == -1) {
                distances[new_row][new_col] = distances[current_row][current_col] + 1;
                queue_insert(queue, (new_row * cols) + new_col);
            }
        }
    }
    int min_distance = -1;
    char closest_digit = '\0';

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] >= '0' && maze[i][j] <= '9' && distances[i][j] != -1) {
                if (min_distance == -1 || distances[i][j] < min_distance) {
                    min_distance = distances[i][j];
                    closest_digit = maze[i][j];
                }
            }
        }
    }
    if (closest_digit != '\0') {
        printf("%c\n", closest_digit);
    } else {
        printf("No reachable digit found.\n");
    }

    queue_delete(queue);
    return 0;
}
