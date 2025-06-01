#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include "../LibraryCPP/queue.h"

void paint_board(int n, int m, int board[100][100]) {
    Queue* q = queue_create();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (board[i][j] > 0) {
                queue_insert(q, i * m + j);
            }
        }
    }

    while (!queue_empty(q)) {
        int cell_index = queue_get(q);
        int x = cell_index / m;
        int y = cell_index % m;

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (abs(dx) + abs(dy) == 1) {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx >= 0 && nx < n && ny >= 0 && ny < m && board[nx][ny] == 0) {
                        board[nx][ny] = board[x][y] + 1;
                        queue_insert(q, nx * m + ny);
                    }
                }
            }
        }

        queue_remove(q);
    }

    queue_delete(q);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }

    
    std::ifstream infile(argv[1]);
    int n, m;
    infile >> n >> m;

    int board[100][100];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            board[i][j] = 0;

    int x, y;
    while (infile >> x >> y) {
        board[x - 1][y - 1] = 1;
    }

    paint_board(n, m, board);

    int max_color = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (board[i][j] > max_color) {
                max_color = board[i][j];
            }

    std::cout << max_color << std::endl;

    return 0;
}   