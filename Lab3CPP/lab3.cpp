#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include "../LibraryCPP/queue.h"

struct Cell {
    int row, col;
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream fin(argv[1]);
    if (!fin) {
        std::cerr << "Error: Cannot open input file " << argv[1] << std::endl;
        return 1;
    }

    int n, m;
    fin >> n >> m;

    std::vector<std::vector<int>> board(n, std::vector<int>(m, 0));
    Queue* queue = queue_create();

    int x, y;
    while (fin >> x >> y) {
        board[x - 1][y - 1] = 1;
        Cell* cell = new Cell{x - 1, y - 1};
        queue_insert(queue, (intptr_t)cell);
    }

    int max_color = 1;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!queue_empty(queue)) {
        Queue* next_queue = queue_create();

        while (!queue_empty(queue)) {
            Cell* current = (Cell*)queue_get(queue);
            queue_remove(queue);

            int cur_row = current->row;
            int cur_col = current->col;

            for (int d = 0; d < 4; ++d) {
                int nx = cur_row + dx[d];
                int ny = cur_col + dy[d];

                if (nx >= 0 && ny >= 0 && nx < n && ny < m && board[nx][ny] == 0) {
                    board[nx][ny] = board[cur_row][cur_col] + 1;
                    Cell* next = new Cell{nx, ny};
                    queue_insert(next_queue, (intptr_t)next);
                }
            }

            delete current;
        }

        queue_delete(queue);
        queue = next_queue;
        max_color++;
    }

    std::cout << max_color - 1 << std::endl;

    queue_delete(queue);
    return 0;
}
