#include <iostream>
#include <fstream>
#include <vector>
#include "../LibraryCPP/queue.h"

using namespace std;

struct Cell {
    int row, col, intensity;
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin) {
        cerr << "Error: Cannot open input file " << argv[1] << endl;
        return 1;
    }

    int n, m;
    fin >> n >> m;

    vector<vector<int>> board(n, vector<int>(m, 0));

    Queue* q = queue_create();

    int x, y;
    while (fin >> x >> y) {
        x--; y--; // Перевод в 0-индексацию
        board[x][y] = 1;
        queue_insert(q, (intptr_t)(new Cell{x, y, 1}));
    }

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    int maxIntensity = 1;

    int count = 0;
    const int maxIterations = n * m;

    while (!queue_empty(q) && count < maxIterations) {
        count++;
        Cell* cell = (Cell*)queue_get(q);
        queue_remove(q);

        for (int d = 0; d < 4; d++) {
            int nx = cell->row + dx[d];
            int ny = cell->col + dy[d];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && board[nx][ny] == 0) {
                board[nx][ny] = cell->intensity + 1;
                if (maxIntensity < cell->intensity + 1)
                    maxIntensity = cell->intensity + 1;
                queue_insert(q, (intptr_t)(new Cell{nx, ny, cell->intensity + 1}));
            }
        }

        delete cell;
    }

    queue_delete(q);

    cout << maxIntensity << endl;

    return 0;
}
