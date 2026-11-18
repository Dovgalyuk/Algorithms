#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"
#include "vector.h"
using namespace std;

int Solve(ifstream &file) {
    int n = 0, m = 0;
    if (!(file >> n >> m)) {
        return 0;
    }
    if (n <= 0 || m <= 0) {
        return 0;
    }

    size_t total_cells = (size_t)(n * m);
    Vector board;
    board.resize(total_cells);
    for (size_t i = 0; i < total_cells; ++i) {
        board.set(i, 0);
    }

    Queue queue;

    int r = 0, c = 0;
    while (file >> r >> c) {
        if (r < 1 || r > n || c < 1 || c > m) {
            continue;
        }

        size_t index = (size_t)((r - 1) * m + (c - 1));
        if (board.get(index) == 0) {
            board.set(index, 1);
            queue.insert((int)index);
        }
    }

    if (queue.empty()) {
        return 0;
    }

    int color = 1;

    while (!queue.empty()) {
        int current = queue.get();
        queue.remove();

        int cr = current / m + 1;
        int cc = current % m + 1;
        color = board.get((size_t)current);

        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        for (int i = 0; i < 4; ++i) {
            int nr = cr + dr[i];
            int nc = cc + dc[i];

            if (nr < 1 || nr > n || nc < 1 || nc > m) {
                continue;
            }

            size_t next_index = (size_t)((nr - 1) * m + (nc - 1));
            if (board.get(next_index) == 0) {
                board.set(next_index, color + 1);
                queue.insert((int)next_index);
            }
        }
    }

    return color;
}

int main(int argc, char* argv[]) {
    string filename = "input1.txt";
    if (argc >= 2) {
        filename = argv[1];
    }
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "файл не найден";
        return 1;
    }

    cout << Solve(file) << "\n";

    file.close();
    return 0;
}
