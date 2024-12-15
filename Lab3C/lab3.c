#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define MAX_N 100
#define MAX_M 100

int board[MAX_N][MAX_M];

void paint_board(int N, int M) {
    Queue* queue = queue_create(NULL);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (board[i][j] > 0) {
                int* cell = malloc(2 * sizeof(int));
                cell[0] = i;
                cell[1] = j;
                queue_insert(queue, cell);
            }
        }
    }

    int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    while (!queue_empty(queue)) {
        int* cell = (int*)queue_get(queue);
        int x = cell[0];
        int y = cell[1];
        int current_color = board[x][y];

        for (int d = 0; d < 4; d++) {
            int new_x = x + directions[d][0];
            int new_y = y + directions[d][1];

            if (new_x >= 0 && new_x < N && new_y >= 0 && new_y < M && board[new_x][new_y] == 0) {
                board[new_x][new_y] = current_color + 1;
                int* new_cell = malloc(2 * sizeof(int));
                if (!new_cell) {
                    fprintf(stderr, "Memory allocation error\n");
                }
                else
                {
                new_cell[0] = new_x;
                new_cell[1] = new_y;
                queue_insert(queue, new_cell);
                }
                
            }
        }

        queue_remove(queue);
        free(cell);
    }

    queue_delete(queue);
}

int main(int argc, char* argv[]) {
    FILE* input_file = fopen(argv[1], "r");

    if (!input_file) {
        return 1;
    }

    int N, M;
    fscanf(input_file, "%d %d", &N, &M);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            board[i][j] = 0;
        }
    }

    int x, y;
    while (fscanf(input_file, "%d %d", &x, &y) == 2) {
        board[x - 1][y - 1] = 1;
    }

    fclose(input_file);

    paint_board(N, M);

    int max_color = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (board[i][j] > max_color) {
                max_color = board[i][j];
            }
        }
    }

    printf("%d\n", max_color);

    return 0;
}
